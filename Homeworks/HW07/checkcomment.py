def check_comment(filename):
    with open(filename) as f:
        lines = f.readlines()
        i = 0
        lines_len = len(lines)
        LoC = 0
        NonBlankLine = 0
        while i < lines_len:
            line = lines[i].lstrip().rstrip()
            if line.find("goto") != -1:
                print("Do not use goto in your code.")
                return False
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
            elif line.find("//") != -1:
                j = i
                NonBlankLine = 0
                LoC += 1
            else:
                LoC += 1
                NonBlankLine += 1
                if NonBlankLine > 4:
                    print("No enough comments at line %d." % (i+1))
                    return False
            i += 1
        print("Lines of code =", LoC)
        if LoC > 500:
            print(
                "More than 500 non blank lines in your code - submission will be ignored.")
            return False

    return True


if __name__ == "__main__":
    import sys

    if len(sys.argv) != 2:
        print("Usage: {} <filename>".format(sys.argv[0]), file=sys.stderr)
        exit(-1)

    ret = check_comment(sys.argv[1])
    exit(0 if ret else 1)
