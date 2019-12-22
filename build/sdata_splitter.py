#!/usr/bin/python

import sys, os

path = "../src/data/sdata/"
filename = "sdata_800AB3BC"
linkerObjFile = "\"..\\obj\\data\\sdata\\" + filename + ".obj\""
fileToOpen = path + filename + ".c"
outFolder = path #+ "test/"
linkerTxtPath = "linker_command_file.txt"

prefix = "int SECTION(\".sdata\") "
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
    if line.find("=") is not -1:
        return True
    else:
        return False

def addToLinker():
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
            if linkerLine.startswith("\tinclude\t" + linkerObjFile ):
                pastHeader = True

            linker.write(linkerLine + "\n")
            idx += 1

def makeFile(line):
    print(line)
    fileName = line[line.find("(\".sdata\") ")+len("(\".sdata\") "):line.find("=") ]
    print("Processing file: " + fileName.rstrip().replace("[]", "") + ".c")
    with open(outFolder.rstrip() + fileName.rstrip().replace("[]", "") + ".c","w+") as write:
        write.write("#include \"linker.h\"")
        write.write("\n\n")
        write.write(line)
        write.write("\n")
            
    objIncludes.append("	include	\"..\\obj\\data\\sdata\\"+fileName.rstrip().replace("[]", "")+".obj\"")
    return line

def tableDetected(line):
    if line.startswith("int"):
        if line.find("[]") is not -1:
            return True
    return False

def hexIncrease(address, number):
    intNum = int(address,16)
    intNum += number
    hexNum = str(hex(intNum))
    hexNum = hexNum[2:].upper()
    return hexNum

def splitTable(line):
    table = []
    dwordPrefixStr = "int SECTION(\".sdata\") "
    namePrefix = line[line.find(dwordPrefixStr)+len(dwordPrefixStr):line.find("[]") - 8]
    address = line[line.find(namePrefix)+len(namePrefix):line.find("[]")]
    tableDataRaw = line[line.find("{")+1:line.find("}")]
    tableDataRaw = tableDataRaw.replace(" ", "")

    while tableDataRaw.find(",") is not -1:
        table.append( dwordPrefixStr + namePrefix + address + " = " + tableDataRaw[:tableDataRaw.find(",")]+ ";")
        tableDataRaw = tableDataRaw[tableDataRaw.find(",")+1:]

        address = hexIncrease(address, 4)
    table.append( dwordPrefixStr + namePrefix + address + " = " + tableDataRaw+ ";")

    return table


def processLine(line):
    tableElements = [ line ]
    if tableDetected(line):
        tableElements = splitTable(line)

    print(tableElements)
    for element in tableElements:
        makeFile(element)

with open(fileToOpen, 'r') as fp:
    line = fp.readline()
    cnt = 1

    while line:
        if cnt > importantLinesStartAt:
            if isLabelStart(line):
                processLine(line)

        line = fp.readline()
        cnt += 1
    addToLinker()
