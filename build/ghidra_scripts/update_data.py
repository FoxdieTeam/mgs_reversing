#@category _MGS

"""
Instructions:

1. The Ghidra parser can't deal with __LINE__, so in linker.h, #define out STATIC_ASSERT_SIZE() to nothing so that you have

    #define STATIC_ASSERT_SIZE(struct, size) 

2. In Ghidra, click on

        File > Parse C Source...
   
   then click on
   
        Save profile to new name
   
   to create a new profile that you can call psx.prf.

   Remove all the source files and options, then individually add each header file in src and its subfolders to the
   list of source files to parse and use the following parse options, replacing Path/to/ as appropriate and adding any
   folders that might be missing from the list. Note that on Linux, you might be required to make all the filenames in
   the PsyQ INCLUDE and INCLUDE/SYS folders lowercase, as well as the INCLUDE/SYS folder name itself.
   
        -IPath/to/mgs_reversing/src
        -IPath/to/mgs_reversing/src/Equip
        -IPath/to/mgs_reversing/src/Font
        -IPath/to/mgs_reversing/src/Game
        -IPath/to/mgs_reversing/src/libdg
        -IPath/to/mgs_reversing/src/libgcl
        -IPath/to/mgs_reversing/src/libgv
        -IPath/to/mgs_reversing/src/map
        -IPath/to/mgs_reversing/src/memcard
        -IPath/to/mgs_reversing/src/Menu
        -IPath/to/mgs_reversing/src/mts
        -IPath/to/mgs_reversing/src/Okajima
        -IPath/to/mgs_reversing/src/Thing
        -IPath/to/mgs_reversing/src/util
        -IPath/to/mgs_reversing/src/Weapon
        -IPath/to/psyq_sdk/psyq_4.3/include
        -Dmips1
        -D__GNUC__
        -D_GNU_SOURCE
        -D__WORDSIZE=32
        -D__builtin_va_list=void *
        -D__DO_NOT_DEFINE_COMPILE
        -D_Complex
        -D_WCHAR_T

3. Now restore the static assert definition to linker.h.

4. Change the root_dir and run it from Ghidra's Script Manager.
"""

import os
import sys
import string
import re
from ghidra.program.model.data import ArrayDataType, DataUtilities

dtm = currentProgram.getDataTypeManager()

root_dir = os.path.realpath(os.path.join(os.path.dirname(__file__), '../../'))

symbol_address_map = { }

with open(root_dir + '/obj/asm.map') as map:
    for line in map:
        pieces = line.split()
        if len(pieces) != 2:
            continue

        symbol = pieces[1]
        if symbol.startswith('_'):
            continue
            
        symbol_address_map[symbol] = pieces[0]

ishex = lambda s: all(c in string.hexdigits for c in s)

defines = { }

# Removes text from in between braces, even if they are nested.
# https://stackoverflow.com/a/14598135
def strip_braces(string):
    ret = ''
    skip1c = 0
    for i in string:
        if i == '{':
            skip1c += 1
        elif i == '}' and skip1c > 0:
            skip1c -= 1
        elif skip1c == 0:
            ret += i
    return ret 

defined_data_ranges = []
updated_keys = set()

for root, subdirs, files in os.walk(root_dir + '/src'):

    for filename in files:
        file_path = os.path.join(root, filename)

        if file_path.endswith('.swp'):
            continue

        with open(file_path, 'r') as f:
        
            lines = f.readlines()
            for index, line in enumerate(lines):
            
                pieces = line.split()
                if (len(pieces) < 3):
                    continue
                    
                if pieces[0] == '#define':
                    defines[pieces[1]] = ' '.join(pieces[2:])
                    continue
                    
                pieces_base_index = 1 if pieces[0] == 'struct' else 0
                
                var_type = pieces[pieces_base_index]
                if var_type.__contains__('/') or var_type == 'char':
                    continue
                    
                data_types = []
                dtm.findDataTypes(var_type, data_types)
                if len(data_types) == 0:
                    continue
                data_type = data_types[0]
                
                var_section = pieces[pieces_base_index + 1]
                if not var_section.startswith('SECTION'):
                    continue
                    
                var_name = pieces[pieces_base_index + 2]
                var_name = var_name.replace(';', '')

                print_debug_info = False # var_name.__contains__('800B05A8') or var_name.__contains__('800B77E8')

                if print_debug_info:
                    print('line == ' + line)

                # Do we have an array?
                if var_name.__contains__(']'):
                    
                    if print_debug_info:
                        print('detected array')

                    penultimate_char = var_name[len(var_name) - 2]
                    num_elements = 1 # For the missing comma, assuming we're not going to end with a comma.
                    
                    if penultimate_char == '[':
                        
                        if print_debug_info:
                            print('number of elements not specified, counting')

                        # Count elements ourselves.
                        next_line_index = index
                        decl_braces_counted = False
                        while True:
                            next_line = lines[next_line_index]
                            if decl_braces_counted:
                                next_line = strip_braces(next_line).partition('//')[0]
                            else:
                                decl_braces_counted = True
                            next_line_pieces = next_line.count(',') # Assuming we're not going to end with a comma.
                            num_elements += next_line_pieces
                            if next_line.__contains__(';'):
                                break
                            next_line_index += 1
                            
                    else:

                        if print_debug_info:
                            print('number of elements specified, retrieving')

                        number_regex = re.findall(r'\[([A-Za-z0-9_]+)\]', var_name)
                        if len(number_regex) == 0:
                            continue

                        if print_debug_info:
                            print('regex found a possible number')
                            
                        possible_number = number_regex[0]
                        if possible_number.isdigit():
                            num_elements = int(possible_number, 10)

                            if print_debug_info:
                                print('found literal with value == ' + str(num_elements))

                        elif possible_number in defines:
                            if (defines[possible_number].isdigit()):
                                num_elements = int(defines[possible_number], 10)

                                if print_debug_info:
                                    print('found use of #define with value == ' + str(num_elements))

                        else:

                            if print_debug_info:
                                print('found use of #define not yet put in dictionary')

                            # @todo: fix headers that contain relevant #defines possibly being read after the files that need them.
                            continue
                    
                    key = var_name.partition('[')[0]
                    if key not in updated_keys and key in symbol_address_map:
                        address = symbol_address_map[key]

                        if print_debug_info:
                            print('key found in symbol-address map with address == ' + address)

                        if ishex(address) and len(address) == 8 and address.startswith('80'):

                            if print_debug_info:
                                print('valid address, adding array')

                            data_type_array = ArrayDataType(data_type, num_elements, data_type.getLength())

                            address_as_int = int(address, 16)
                            end_address_as_int = address_as_int + data_type_array.getLength() - 1
                            for start_end_pairs in defined_data_ranges:
                                defined_data_start = start_end_pairs[0]
                                defined_data_end = start_end_pairs[1]
                                if address_as_int <= defined_data_end and end_address_as_int >= defined_data_start:
                                    print('WARNING: OVERLAPPING DATA')
                                    print(var_name + ' in range ' + address + ' - ' + hex(end_address_as_int))
                                    print('overlaps ' + getSymbolAt(toAddr(defined_data_start)).getName() + ' in range ' + hex(defined_data_start) + ' - ' + hex(defined_data_end))
                                    print('*****************************')
                            defined_data_ranges.append((address_as_int, end_address_as_int))
                            start_address = toAddr(address_as_int)
                            end_address = toAddr(end_address_as_int)

                            clearListing(start_address, end_address)
                            DataUtilities.createData(currentProgram, start_address, data_type_array, data_type_array.getLength(), True, DataUtilities.ClearDataMode.CLEAR_SINGLE_DATA)

                            updated_keys.add(key)

                            if print_debug_info:
                                # exit()
                                print('*****************************')
                        
                else:

                    if print_debug_info:
                        print('detected single element')

                    if var_name not in updated_keys and var_name in symbol_address_map:
                        base_address = symbol_address_map[var_name]

                        if print_debug_info:
                            print('key found in symbol-address map with base_address == ' + base_address)

                        if ishex(base_address) and len(base_address) == 8 and base_address.startswith('80'):

                            if print_debug_info:
                                print('valid address, adding element')

                            address_as_int = int(base_address, 16)
                            end_address_as_int = address_as_int + data_type.getLength() - 1
                            for start_end_pairs in defined_data_ranges:
                                defined_data_start = start_end_pairs[0]
                                defined_data_end = start_end_pairs[1]
                                if address_as_int <= defined_data_end and end_address_as_int >= defined_data_start:
                                    print('WARNING: OVERLAPPING DATA')
                                    print(var_name + ' in range ' + base_address + ' - ' + hex(end_address_as_int))
                                    print('overlaps ' + getSymbolAt(toAddr(defined_data_start)).getName() + ' in range ' + hex(defined_data_start) + ' - ' + hex(defined_data_end))
                                    print('*****************************')
                            defined_data_ranges.append((address_as_int, end_address_as_int))
                            start_address = toAddr(address_as_int)
                            end_address = toAddr(end_address_as_int)

                            clearListing(start_address, end_address)
                            DataUtilities.createData(currentProgram, start_address, data_type, data_type.getLength(), True, DataUtilities.ClearDataMode.CLEAR_SINGLE_DATA)

                            updated_keys.add(var_name)

                            if print_debug_info:
                                # exit()
                                print('*****************************')
