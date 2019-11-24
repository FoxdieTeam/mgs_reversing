def process(line):
    # remove TEXT:80010000
    line = line[14:]

    # fix comments
    line = line.replace("# ","; ");

    # fix ascii nulls and \n's
    if line.find(".ascii") != -1:
        line = line.replace('"<0>', '\", 0x0')
        line = line.replace('\\n"', '\", 0xA')

    # fix escape seq
    line = line.replace('\\"', '""')

    # fix data types        
    line = line.replace(".ascii", "db")
    line = line.replace(".byte", "db")
    line = line.replace(".half", "dh")
    line = line.replace(".word", "dw")
  
    return line

with open("file.txt", "r") as ins:
    with open('output.txt', 'w') as the_file:
        for line in ins:
            line = process(line)
            the_file.write(line)
