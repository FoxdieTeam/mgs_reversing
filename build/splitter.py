#!/usr/bin/python
# Usage or whatever: 
# python splitter.py <file> <optional_outfolder>

import sys, os

fileToOpen = "../asm/rom3.s"
outFolder = "../asm/" #"test/"
linkerTxtPath = "linker_command_file.txt"
importantLinesStartAt = 2

objIncludes = []

if len(sys.argv) < 2:
    print("Usage:")
    print("python splitter.py <file> <optional_outfolder>")
    exit()

if len(sys.argv) >= 2:
    fileToOpen = str(sys.argv[1])

if len(sys.argv) >= 3:
    outFolder = str(sys.argv[2])

if not os.path.exists(outFolder):
    os.makedirs(outFolder)

def isLabelStart(line):
    if line.startswith("	xdef "):
        return True
    else:
        return False

def addToLinker(fileName):
    oldLinker = False
    with open(linkerTxtPath,"r") as linker:
        oldLinker = linker.read().splitlines()

    pastHeader = False
    onlyOnce = True
    idx = 1
    with open(linkerTxtPath,"w") as linker:
        while idx < len(oldLinker):
            linkerLine = oldLinker[idx]
            if len(linkerLine) == 1 and pastHeader and onlyOnce:
                for objInclude in objIncludes:
                    linker.write(objInclude + "\n")
                onlyOnce = False
            if linkerLine.startswith("; link objs"):
                pastHeader = True

            linker.write(linkerLine + "\n")
            idx += 1

def makeFile(fp, line):
    fileName = line[line.find("	xdef ")+6:]
    print("Processing file: " + fileName.rstrip() + ".s")
    with open(outFolder.rstrip() + fileName.rstrip() + ".s","w+") as write:
        write.write("	opt	c+, at+, e+, n-")
        write.write("")
        write.write(line)

        line = fp.readline()
        while len(line) > 1:
            write.write(line)
            line = fp.readline()

    objIncludes.append("	include	\"..\\obj\\"+fileName.rstrip()+".obj\"")
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