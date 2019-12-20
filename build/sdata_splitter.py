#!/usr/bin/python

import sys, os

path = "../src/data/sbss/"
filename = "sbss_800AB9CC"
linkerObjFile = "\"..\\obj\\data\\sbss\\" + filename + ".obj\""
fileToOpen = path + filename + ".c"
outFolder = path #+ "test/"
linkerTxtPath = "linker_command_file.txt"

prefix = "int SECTION(\".sbss\") "
importantLinesStartAt = 2

objIncludes = []

# if len(sys.argv) < 2:
#     print("Usage:")
#     print("python splitter.py <file> <optional_outfolder>")
#    exit()

if len(sys.argv) >= 2:
    fileToOpen = str(sys.argv[1])

if len(sys.argv) >= 3:
    outFolder = str(sys.argv[2])

if not os.path.exists(outFolder):
    os.makedirs(outFolder)

def isLabelStart(line):
    if line.startswith(prefix):
        return True
    else:
        return False

def addToLinker(fileName):
    oldLinker = False
    with open(linkerTxtPath,"r") as linker:
        oldLinker = linker.read().splitlines()

    pastHeader = False
    onlyOnce = True
    idx = 0
    with open(linkerTxtPath,"w") as linker:
        while idx < len(oldLinker):
            linkerLine = oldLinker[idx]
            if pastHeader and onlyOnce:
                for objInclude in objIncludes:
                    linker.write(objInclude + "\n")
                onlyOnce = False
            print("	include	" + linkerObjFile)
            if linkerLine.startswith("\tinclude " + linkerObjFile ):
                pastHeader = True

            linker.write(linkerLine + "\n")
            idx += 1

def makeFile(fp, line):
    fileName = line[line.find(prefix) + len(prefix):]
    print("Processing file: " + fileName.rstrip()[:-1] + ".c")
    with open(outFolder.rstrip() + fileName.rstrip()[:-1] + ".c","w+") as write:
        write.write("#include \"linker.h\"")
        write.write("\n\n")
        write.write(line)
            
    objIncludes.append("	include	\"..\\obj\\data\\sbss\\"+fileName.rstrip()[:-1]+".obj\"")
    return fp, line

with open(fileToOpen, 'r') as fp:
    line = fp.readline()
    cnt = 1

    while line:
        if cnt > importantLinesStartAt:
            if isLabelStart(line):
                fp, line = makeFile(fp, line)

        line = fp.readline()
        cnt += 1
    addToLinker(objIncludes)
