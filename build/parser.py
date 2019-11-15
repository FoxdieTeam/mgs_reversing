fileToOpen = "../asm/rom_sdata.s"
importantLinesStartAt = 15

def peekLine(fp):
    pos = fp.tell()
    line = fp.readline()
    fp.seek(pos)
    return line

def removeColonSubstr(line, varType):
    colonIdx = line.find(":")
    colonEnd = line.find(varType, colonIdx)
    return line[:colonIdx] + line[colonEnd:]

def removeComment(line):
    #TODO make them C comments instead
    commentIdx = line.find(";")
    if commentIdx:
        line = line[:commentIdx]

    # Get rid of spaces, too
    while True:
        if line[-1] == " ":
            line = line[:-1]
        else:
            break
    return line

def isTableAlready(line):
    if line.find("[]") != -1:
        return True
    return False

def makeLineTable(line):
    if not isTableAlready(line):
        putStartBracketHere = line.find(" = ")
        line = line[:putStartBracketHere + 3] + "{" + line[putStartBracketHere + 3:] + '}'
        line = line.replace(" = ", "[] = ")
    return line

def appendTableElems(tableElems, line):
    if len(tableElems) == 0:
        return line

    line = makeLineTable(line)
    for i in range(len(tableElems)):
        line = line.replace('}', "," + tableElems[i] + "}")

    return line

def handleOneLineTables(line):
    comma = line.find(",")
    if comma != -1:
        line = makeLineTable(line)
    return line

def handleMultipleLines(line, fp, varType):
    # handle next lines until another label is found
    additionalTableVars = []
    while True:
        currPos = fp.tell()
        lineCandidate = fp.readline()
        if not lineCandidate.startswith(" "):
            fp.seek(currPos)
            break

        #handling next lines (assuming it's a continued table)
        toRemove = lineCandidate.find(varType + " ")
        lineCandidate = lineCandidate[toRemove + 3:]
        while True:
            comma = lineCandidate.find(",")
            if comma != -1:
                additionalTableVars.append(lineCandidate[:comma])
                lineCandidate = lineCandidate[comma + 1:]
            else:
                additionalTableVars.append(lineCandidate[:comma])
                break
        #print(additionalTableVars)

    line = appendTableElems(additionalTableVars, line)
    return line, fp

with open(fileToOpen, 'r') as fp:
    line = fp.readline()
    cnt = 1

    while line:
        if cnt > importantLinesStartAt:
            line = removeComment(line)

            # c string
            if line.startswith('a'):
                line = "char SECTION(\".sdata\") " + line
                line = removeColonSubstr(line, "db")
                line = line.replace("db", "[] =")

                line = line.replace("\", 0xA", "\\n\"")

                # Remove string junk
                line = line.replace(", 0x0", ";")

                print(line)
                # handle next lines until another label is found
                while True:
                    currPos = fp.tell()
                    lineCandidate = fp.readline()
                    if not lineCandidate.startswith(" "):
                        fp.seek(currPos)
                        break
                    # ignoring those additional string lines - useless
                
            elif line.startswith("byte"):
                line = "char SECTION(\".sdata\") " + line
                line = removeColonSubstr(line, "db")
                line = line.replace("db ", " = ")

                line = handleOneLineTables(line)
                line, fp = handleMultipleLines(line, fp, "db")

                line = line + ";"
                print(line)

            if line.startswith("dword"):
                line = "int SECTION(\".sdata\") " + line
                line = removeColonSubstr(line, "dw")
                line = line.replace("dw ", " = ")

                line = handleOneLineTables(line)
                line, fp = handleMultipleLines(line, fp, "dw")

                line = line + ";"
                print(line)

        line = fp.readline()
        cnt += 1


