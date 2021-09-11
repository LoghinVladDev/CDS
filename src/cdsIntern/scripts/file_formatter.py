from sys import argv


def main():
    if len(argv) == 0:
        print('Requires at least a file as argument')
        return

    try:
        with open(argv[1]) as source:
            print(source.read())

    except Exception as cannot_open:
        print(f'Error : {cannot_open}')


if __name__ == '__main__':
    main()
