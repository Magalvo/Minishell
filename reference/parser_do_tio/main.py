from parser import parser

def parse_command(command):
    result = parser.parse(command)
    return result

if __name__ == "__main__":
    while True:
        try:
            s = input('bash > ')
        except EOFError:
            break
        if not s:
            continue
        result = parse_command(s)
        if result:
            print(result)
