def process(line):
    parts = line.strip().split(" ")
    parts = filter(None, parts)
    if len(parts) == 2:
        if not parts[1].endswith("_ORGEND") and not parts[1].endswith("_OBJEND") and not parts[1].endswith("_OBJ") and not parts[1].endswith("_ORG"):
            print parts[0]
            print parts[1]

with open("..\\obj\\asm.map", "r") as ins:
    foundStart = False
    for line in ins:
        if foundStart:
            process(line)

        if "Address  Names in address order" in line:
            foundStart = True

