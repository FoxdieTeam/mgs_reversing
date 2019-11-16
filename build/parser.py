fileToOpen = "../asm/rom_rdata.s"
importantLinesStartAt = 92
rData = True

sectionString = "sdata"
if rData:
    sectionString = "RDATA"

byteCrapCounter = 2
wordCrapCounter = 9
stringCrapCounter = 0

#TODO parse header

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
    commentIdx = -1
    inQuotes = False
    for i, c in enumerate(line):
        if c == "\"":
            inQuotes = not inQuotes
        if c == ";" and not inQuotes:
            commentIdx = i
            break

    if commentIdx != -1:
        line = line[:commentIdx]
        # Get rid of spaces, too
        while True:
            if len(line) > 0 and line[-1] == " ":
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
        line = line[:putStartBracketHere + 3] + "{" + line[putStartBracketHere + 3:].rstrip() + '}'
        line = line.replace(" = ", "[] = ")
    return line

def appendTableElems(tableElems, line):
    if len(tableElems) == 0:
        return line

    line = makeLineTable(line)
    for i in range(len(tableElems)):
        line = line.replace('}', ", " + tableElems[i] + "}")

    return line

def handleOneLineTables(line):
    if line.find(",") != -1:
        line = makeLineTable(line)
    return line

def anotherLabelFound(line, varType):
    varTypes = ["db", "dw"]
    varTypes.remove(varType)
    for varT in varTypes:
        if line.find(varT) != -1:
            return True
    return False

def isLineJustComment(line):
    for i, c in enumerate(line):
        if c != " " and c != ";":
            return False
        if c == ";":
            return True

def handleMultipleLines(line, fp, varType):
    # handle next lines until another label is found
    additionalTableVars = []
    while True:
        currPos = fp.tell()
        lineCandidate = fp.readline()
        if isLineJustComment(lineCandidate):
            currPos = fp.tell()
            lineCandidate = fp.readline()

        if not lineCandidate.startswith(" ") or (not lineCandidate.startswith(" ") and not anotherLabelFound(lineCandidate, varType)):
            fp.seek(currPos)
            break

        if isLineJustComment(lineCandidate):
            continue

        #handling next lines (assuming it's a continued table)
        lineCandidate = removeComment(lineCandidate)
        toRemove = lineCandidate.find(varType + " ")
        lineCandidate = lineCandidate[toRemove + 3:]
        while True:
            comma = lineCandidate.find(",")
            if comma != -1:
                additionalTableVars.append(lineCandidate[:comma].rstrip())
                lineCandidate = lineCandidate[comma + 2:] #skip comma and space
            else:
                additionalTableVars.append(lineCandidate.rstrip())
                break
        #print(additionalTableVars)

    line = appendTableElems(additionalTableVars, line)
    return line, fp

def isLineStrayString(line):
    if line.find("\"") != -1 and line.startswith(" "):
        return True
    return False

def handleStrayLabels(line):
    if isLineStrayString(line):
        global stringCrapCounter
        line =  "aString_" + "crap" + str(stringCrapCounter) + ":" + line
    elif line.startswith(" "):
        if line.find("db") != -1:
            global byteCrapCounter
            line = "byte_" + "crap" + str(byteCrapCounter) + ":" + line
            byteCrapCounter += 1
        elif line.find("dw") != -1:
            global wordCrapCounter
            line = "dword_" + "crap" + str(wordCrapCounter) + ":" + line
            wordCrapCounter += 1
        # print("stray line")
        # print(line, end="")
    return line

def isJustDbZero(line):
    if line.rstrip().endswith("0"):
        for c in reversed(line.rstrip()):
            if c != "d" and c != "b" and c != " " and c != "0":
                return False
        return True
    return False

def handleQuotesInString(line):
    startIdx = -1
    endIdx = line.rfind("\"")
    inQuotes = False
    for i, c in enumerate(line):
        if c == "\"" and line[i+1] == "\"" and inQuotes and i != startIdx and i+1 != endIdx:
            line = line[:i] + "\\" + line[i + 1:]
        if c == "\"" and not inQuotes:
            inQuotes = True
            startIdx = i
    return line

def parse(line, fp):
    global sectionString
    line = handleStrayLabels(line)

    # c string
    if line.startswith('a'):
        line = handleQuotesInString(line)
        if rData:
            line = "const char SECTION(\".RDATA\") " + line
        else:
            line = "char SECTION(\".sdata\") " + line
        line = removeColonSubstr(line, "db")
        line = line.replace("db ", "[] = ")

        line = line.replace("\", 0xA", "\\n\"")

        # Remove string junk
        if line.rstrip().endswith(", 0x0"):
            line = line.replace(", 0x0", ";")
        else:
            line = line + ";"

        print(line.rstrip())
        # handle next lines until another label is found
        while True:
            currPos = fp.tell()
            lineCandidate = fp.readline()
            if not isJustDbZero(lineCandidate) and not lineCandidate.rstrip().endswith("db 0, 0, 0") and not lineCandidate.endswith("dh 0") and not isLineJustComment(lineCandidate):
                fp.seek(currPos)
                break
            # ignoring those additional string lines - useless

    elif line.startswith("byte"):
        line = "char SECTION(\"." + sectionString + "\") " + line
        line = removeColonSubstr(line, "db")
        line = line.replace("db ", " = ")

        line = handleOneLineTables(line)
        line, fp = handleMultipleLines(line, fp, "db")
        line = line.rstrip()
        line = line + ";"
        print(line)

    if line.startswith("dword") or line.startswith("jpt"):
        line = "int SECTION(\"." + sectionString + "\") " + line
        line = removeColonSubstr(line, "dw")
        line = line.replace("dw ", " = ")

        line = handleOneLineTables(line)
        line, fp = handleMultipleLines(line, fp, "dw")
        line = line.rstrip()
        line = line + ";"
        print(line)
    return line, fp

with open(fileToOpen, 'r') as fp:
    line = fp.readline()
    cnt = 1

    while line:
        if cnt > importantLinesStartAt:
            line = removeComment(line)
            line, fp = parse(line, fp)

        line = fp.readline()
        cnt += 1
