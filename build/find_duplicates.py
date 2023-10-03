#!/usr/bin/env python3

from fnmatch import fnmatch
from glob import glob
import os
from objlib.obj import get_obj_funcs
from statistics import quantiles
from termcolor import colored
from Levenshtein import ratio

obj_dir = os.path.realpath(os.path.join(os.path.dirname(__file__), '../obj'))
asm_dir = os.path.realpath(os.path.join(os.path.dirname(__file__), '../asm'))

def load_all_funcs():
    funcs = {}

    for obj_file in glob(os.path.join(obj_dir, '**/*.obj'), recursive=True):
        for func_name, code in get_obj_funcs(obj_file):
            code = b''.join(code for _, code in code)
            funcs[func_name.decode("utf-8")] = code

    return funcs

def not_matched_functions():
    return set(os.path.basename(f).replace('.s', '') for f in glob(os.path.join(asm_dir, '**/*.s'), recursive=True))

def byte_equality_distance(lhs_func, rhs_func):
    # Naive approach: how many bytes are different in equal-sized funcs
    if len(lhs_func) != len(rhs_func):
        return None

    return sum(1 if lhs_byte != rhs_byte else 0 for lhs_byte, rhs_byte in zip(lhs_func, rhs_func))

def levenshtein_distance_on_bytes(lhs_func, rhs_func):
    return int((1.0 - ratio(lhs_func, rhs_func)) * 100)

def quantiles_wrapper(data, n):
    if len(data) == 1:
        return [data[0] for _ in range(n)]
    return quantiles(data, n=n)

def main():
    # Legend
    print(colored('Legend', 'white', attrs=['underline']))
    print('  Matches:', colored('PERFECT MATCH', 'green', attrs=['reverse']),
        colored('good match', 'green'), colored('OK match', 'white', attrs=['dark']),
        colored('mediocre match', 'yellow'), colored('bad match', 'red'))
    print('  Functions:', colored('B', 'white', attrs=['bold']), "(big function)", ". (small function)")
    print('')

    # Load all functions
    print('Loading all functions... ', end='', flush=True)
    funcs = load_all_funcs()
    print('\r', end='')

    # Decide which functions to actually compare
    lhs_pattern = input('Left-hand side of comparison - glob filter (e.g. *, sub_8034*, *s00a*, s???r_*): ')
    lhs_only_not_matched = input('Left-hand side of comparison - only not matched functions? y/n ').strip().lower()
    if lhs_only_not_matched == 'y' or lhs_only_not_matched == 'yes':
        lhs_only_not_matched = True
    elif lhs_only_not_matched == 'n' or lhs_only_not_matched == 'no':
        lhs_only_not_matched = False
    else:
        print("Invalid choice:", lhs_only_not_matched)
        sys.exit(1)

    rhs_pattern = input('Right-hand side of comparison - glob filter (e.g. *, sub_8034*, *s00a*, s???r_*): ')
    print('Diffing algorithm:')
    print("  1. Byte equality: fastest, compares how many bytes")
    print("     are different between functions of the same size,")
    print("     so it can detect fully identical functions or functions")
    print("     that differ in relocations.")
    print("  2. Levensthein distance (on pure bytes): slowest")
    algorithm = input('Diffing algorithm (1 or 2): ').strip()
    if algorithm == '1':
        calc_distance = byte_equality_distance
    elif algorithm == '2':
        calc_distance = levenshtein_distance_on_bytes
    else:
        print("Invalid choice of algorithm:", algorithm)
        sys.exit(1)

    print('Comparing... ', end='', flush=True)

    lhs_funcnames = [name for name in funcs if fnmatch(name, lhs_pattern)]
    rhs_funcnames = [name for name in funcs if fnmatch(name, rhs_pattern)]

    lhs_funcnames = sorted(lhs_funcnames, key=lambda x: x.upper()[-8:])
    rhs_funcnames = sorted(rhs_funcnames, key=lambda x: x.upper()[-8:])

    if lhs_only_not_matched:
        allowed_funcs = not_matched_functions()
        lhs_funcnames = [f for f in lhs_funcnames if f in allowed_funcs]

    # Compare the functions, we love O(N^2):
    results = {}
    for lhs_funcname in lhs_funcnames:
        distances = []
        for rhs_funcname in rhs_funcnames:
            if lhs_funcname == rhs_funcname:
                continue
            distance = calc_distance(funcs[lhs_funcname], funcs[rhs_funcname])
            if distance is None:
                continue
            distances.append((rhs_funcname, distance))
        distances = sorted(distances, key=lambda v: v[1])
        distances = distances[:3] # Top 3
        results[lhs_funcname] = distances

    print('\r', len('Comparing... ') * ' ')

    # Prepare for displaying the results
    all_distances = [distance for sublist in results.values() for name, distance in sublist]
    percentiles = quantiles_wrapper(sorted(all_distances), n=100)

    # green - best matches
    # white - in-between
    # yellow - in-between
    # red - worst matches
    green_percentile = percentiles[25]
    white_percentile = percentiles[50]
    yellow_percentile = percentiles[75]

    percentiles = quantiles_wrapper(sorted(len(funcs[func]) for func in lhs_funcnames), n=100)
    small_function = percentiles[25]
    big_function = percentiles[75]

    # Display the results
    for lhs_funcname in lhs_funcnames:
        result = results[lhs_funcname]

        function_indicator = ' '
        if len(funcs[lhs_funcname]) > big_function:
            function_indicator = colored('B', 'white', attrs=['bold'])
        elif len(funcs[lhs_funcname]) < small_function:
            function_indicator = '.'

        print(f"{lhs_funcname} ({len(funcs[lhs_funcname])} bytes)".rjust(50, ' '), function_indicator, end=' | ')
        for name, dist in result:
            attrs = []
            if dist <= green_percentile:
                color = 'green'
                if dist == 0:
                    # Perfect match!
                    attrs.append('reverse')
            elif dist <= white_percentile:
                color = 'white'
                attrs.append('dark')
            elif dist <= yellow_percentile:
                color = 'yellow'
            else:
                color = 'red'
            print(colored(f"{name} ({dist} diff)", color, attrs=attrs), end=' ')
        print('')


if __name__ == '__main__':
    main()
