import os
from idautils import *
from idaapi import *
from idc import *

# This script syncs the psyq .map output into IDA - as the map file only contains
# ALL_CAPS_NAMES it does a slow look up to find out what the real case should be.

# Set to your repo root
root = "E:\\Data\\mgs\\mgs_reversing"

def is_src_file(file):
    return file.endswith(".c") or file.endswith(".C") or file.endswith(".h") or file.endswith(".s") or file.endswith(".S")

def get_all_source_files():
    global root
    srcFiles = []
    for root, dirs, files in os.walk(root + "\\src"):
        for file in files:
            if is_src_file(file):
                srcFiles.append(os.path.join(root, file))
                
    for root, dirs, files in os.walk(root + "\\asm"):
        for file in files:
            if is_src_file(file):
                srcFiles.append(os.path.join(root, file))
    return srcFiles

def get_all_source_files_content(srcFiles):
    allData = []
    for fileName in srcFiles:
        with open(fileName, 'r') as file:
            allData.append(file.read())
    return allData

def correct_case_symbol(sym, allData):
    for fileData in allData:
        idx = fileData.upper().find(sym)
        if idx != -1:
            return fileData[idx, len(sym)]
    return sym

def ida_func_exists(function_address):
    for segment in Segments():
        # get all functions
        for function_ea in Functions(segment, SegEnd(segment)):
            if function_address == function_ea:
                return True
    return False

def sync_function_name(adddress, name):
    if ida_func_exists(adddress):
        currentName = GetFunctionName(adddress)
        if currentName != name:
            print "rename: " + currentName + " to " + name
            idc.MakeNameEx(adddress, name, idc.SN_NOWARN)

def process_map_file_line(line, allData):
    parts = line.strip().split(" ")
    parts = filter(None, parts) # Remove empty entries
    if len(parts) == 2:
        symbol_address = parts[0]
        symbol = parts[1]
        if not symbol.endswith("_ORGEND") and not symbol.endswith("_OBJEND") and not symbol.endswith("_OBJ") and not symbol.endswith("_ORG"):
            if not symbol.upper().startswith("SUB_"): # ignore sub_addr symbols as they haven't been renamed yet
                symbolAddressInt = int(symbol_address, 16)
                symbolFixedCase = correct_case_symbol(symbol, allData)
                sync_function_name(symbolAddressInt, symbolFixedCase)

def sync_map_to_ida():
    global root
    allData = get_all_source_files_content(get_all_source_files())
    with open(root + "\\..\\obj\\asm.map", "r") as ins:
        foundStart = False
        for line in ins:
            if foundStart:
                process_map_file_line(line, allData)

            if "Address  Names in address order" in line:
                foundStart = True

sync_map_to_ida()
