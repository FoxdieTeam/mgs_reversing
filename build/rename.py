import os.path
from os import path

old = "null_printf_8008BBA8"
parts = old.split('_')
newFileName = "mts_null_printf" + "_" + parts[len(parts)-1]
newFuncName = newFileName
subdir = "mts"

def FixFileContent(fileName, find, replace):
    with open(fileName,'r') as f:
        newlines = []
        for line in f.readlines():
            newlines.append(line.replace(find, replace))

    with open(fileName, 'w') as f:
        for line in newlines:
            f.write(line)

oldFile = "..\\asm\\" + subdir + "\\" + old + ".s"
newFile =  "..\\asm\\" + subdir + "\\" + newFileName + ".s"
if path.exists(oldFile):
    os.rename(oldFile, newFile)
    FixFileContent(newFile, old, newFuncName)
    FixFileContent("..\\build\\linker_command_file.txt", old, newFileName)
else:
    print "Couldn't find ..\\asm\\" + old + ".s"
    
print old + " -> " + newFuncName
