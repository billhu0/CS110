#!python3

file = open("ringbuffer.c", 'r')
lines = file.readlines()
i = 0
lines_len = len(lines)
LoC = 0
NonBlankLine = 0
while i < lines_len:
    line = lines[i].lstrip().rstrip()
    if line.find("goto") != -1:
        print("Do not use goto in your code!")
        file.close()
        exit(1)
    elif line == "" or line == "{" or line == "}" or line.find("#include") != -1:
        pass
    elif line.find("/*") != -1:
        j = i
        NonBlankLine = 0
        if line[:2] != "/*":
            LoC += 1
        while line.find("*/") == -1 and i < lines_len:
            i += 1
            line = lines[i].lstrip().rstrip()
        if i > j and line[-2:] != "*/":
            LoC += 1
    else:
        LoC += 1
        NonBlankLine += 1
        if NonBlankLine >= 5:
            print("Not enough comments!")
            file.close()
            exit(1)
    i += 1
print("Lines of code =", LoC)
if LoC > 250:
    print("More than 250 non blank lines in your code - ignoring submission!")
    file.close()
    exit(1)
file.close()
