import os.path
from os import path

old = "sub_" + "80033F88"
parts = old.split('_')
newFileName = "item_kill" + "_" + parts[len(parts)-1]
newFuncName = newFileName


def FixFileContent(fileName, find, replace):
    with open(fileName,'r') as f:
        newlines = []
        for line in f.readlines():
            newlines.append(line.replace(find, replace))

    with open(fileName, 'w') as f:
        for line in newlines:
            f.write(line)
        
if path.exists("..\\asm\\" + old + ".s"):
    os.rename("..\\asm\\" + old + ".s", "..\\asm\\" + newFileName + ".s")
    FixFileContent("..\\asm\\" + newFileName + ".s", old, newFuncName)
    FixFileContent("..\\build\\linker_command_file.txt", old, newFileName)
else:
    print "Couldn't find ..\\asm\\" + old + ".s"
    
