fileToOpen = "../asm/rom_data.s"
importantLinesStartAt = 114
sectionString = "ASM_DATA"
rData = False

byteCrapCounter = 2
dwordCrapCounter = 20
wordCrapCounter = 0
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

    tableStart = line.find("= {")+3
    lineElems = line[tableStart:-1].rstrip().split(", ")
    # print("lineElems for: " + line)
    # print(lineElems)
    resultLine = line[:tableStart]
   
    for i in range(len(lineElems)):
        if lineElems[i].startswith("a") or lineElems[i].startswith("dword"):
            lineElems[i] = handleExternalStrings(lineElems[i])
        if i == 0:
            resultLine += lineElems[i]
        else:
            resultLine += ", " + lineElems[i]
    
    resultLine += "}"

    # while True:
    #     comma = lineCandidate.find(",")
    #     if comma != -1:
    #         if lineCandidate[:comma].rstrip().startswith("a") or lineCandidate[:comma].rstrip().startswith("dword"):
    #             lineCandidate[:comma] = handleExternalStrings(lineCandidate[:comma].rstrip())
    #         lineCandidate = lineCandidate[comma + 2:] 
    #     else:
    #         print(lineCandidate)
    #         if lineCandidate.rstrip().startswith("a") or lineCandidate.rstrip().startswith("dword"):
    #             lineCandidate = handleExternalStrings(lineCandidate.rstrip())
    #         break
    return resultLine

def appendTableElems(tableElems, line):
    if len(tableElems) == 0:
        return line

    line = makeLineTable(line)
    for i in range(len(tableElems)):
        if tableElems[i].startswith("a") or tableElems[i].startswith("dword"):
            tableElems[i] = handleExternalStrings(tableElems[i])
        line = line.replace('}', ", " + tableElems[i] + "}")

    return line

def handleOneLineTables(line):
    if line.find(",") != -1:
        line = makeLineTable(line)
    return line

def anotherLabelFound(line, varType):
    varTypes = ["db", "dw", "dh"]
    varTypes.remove(varType)
    for varT in varTypes:
        if line.find(varT) != -1:
            #print("YES")
            return True
    #print("NO")
    return False

def isLineJustComment(line):
    for i, c in enumerate(line):
        if c != " " and c != ";":
            return False
        if c == ";":
            return True


def handleExternalStrings(string):

    origString = string
    string = string.replace("}", "")

    fileName = "temp.txt"
    with open(fileName, "a+") as write:
        write.write("extern const char* "+string+"[];\n")



    return "(int)"+origString

def handleMultipleLines(line, fp, varType):
    # handle next lines until another label is found
    additionalTableVars = []
    while True:
        currPos = fp.tell()
        lineCandidate = fp.readline()
        if isLineJustComment(lineCandidate):
            currPos = fp.tell()
            lineCandidate = fp.readline()

        #print("candidate: "+lineCandidate)
        if not lineCandidate.startswith(" ") or anotherLabelFound(lineCandidate, varType):
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
        elif line.find("dh") != -1:
            global wordCrapCounter
            line = "word_" + "crap" + str(wordCrapCounter) + ":" + line
            wordCrapCounter += 1
        elif line.find("dw") != -1:
            global dwordCrapCounter
            line = "dword_" + "crap" + str(dwordCrapCounter) + ":" + line
            dwordCrapCounter += 1
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

def getLabel(line):
    # on premodified string
    idx = line.rstrip().find(":")
    return line[:idx+1]

def parse(line, fp):
    global sectionString
    line = handleStrayLabels(line)

    # c string
    if line.startswith('a'):
        label = getLabel(line)
        line = handleQuotesInString(line)
        if rData:
            line = "const char SECTION(\"."+sectionString+"\") " + line
        else:
            line = "char SECTION(\"."+sectionString+"\") " + line
        line = removeColonSubstr(line, "db")
        line = line.replace("db ", "[] = ")

        line = line.replace("\", 0xA", "\\n\"")

        # Remove string junk
        if line.rstrip().endswith(", 0x0"):
            line = line.replace(", 0x0", ";")
        else:
            line = line + ";"

        if line.rstrip().endswith("= \"\\n\";"):
            oldLine = line
            line = fp.readline()
            if not isLineJustComment(line):
                line = label + line
                breakIdx = line.find("\"")
                line = line[:breakIdx] + "\"\\n" + line[breakIdx + 1:]

                line = handleQuotesInString(line)
                if rData:
                    line = "const char SECTION(\"."+sectionString+"\") " + line
                else:
                    line = "char SECTION(\"."+sectionString+"\") " + line
                line = removeColonSubstr(line, "db")
                line = line.replace("db ", "[] = ")

                line = line.replace("\", 0xA", "\\n\"")

                # Remove string junk
                if line.rstrip().endswith(", 0x0"):
                    line = line.replace(", 0x0", ";")
                else:
                    line = line + ";"
            else:
                line = oldLine


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

    elif line.startswith("word"):
        line = "short SECTION(\"." + sectionString + "\") " + line
        line = removeColonSubstr(line, "dh")
        line = line.replace("dh ", " = ")

        line = handleOneLineTables(line)
        line, fp = handleMultipleLines(line, fp, "dh")
        line = line.rstrip()
        line = line + ";"
        print(line)

    if line.startswith("dword") or line.startswith("jpt") or line.startswith("off"):
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
