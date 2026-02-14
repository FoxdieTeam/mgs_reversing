from idautils import *
from idaapi import *
from idc import *

def ida_set_function_colour(function_address, colour):
    idc.set_color(function_address, CIC_FUNC, colour)

def ida_get_function_colour(function_address):
    function = idaapi.get_func(function_address)
    if not function:
        return 0
    return function.color

def ida_func_exists(function_address):
    for segment in Segments():
        # get all functions
        for function_ea in Functions(segment, idc.get_segm_end(segment)):
            if function_address == function_ea:
                return True
    return False

def sync_function_name(adddress, name):
    if ida_func_exists(adddress):
        currentName = idc.get_func_name(adddress)
        if currentName != name:
            print(hex(adddress) +  " rename: " + currentName + " to " + name)
            idc.set_name(adddress, name, idc.SN_CHECK)
 
def main():
    with open('C:\\data\\mgs_reversing\\build\\matched.txt', 'r') as f:
        for line in f:
            address = line.strip()
            addrInt = int(address, 16)
            if ida_func_exists(addrInt):
                ida_set_function_colour(addrInt, 0x0)

if __name__ == '__main__':
    main()
