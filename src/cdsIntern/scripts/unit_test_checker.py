from sys import argv

out_file = open('output.txt', 'w')

def norm_class_name(class_name: str) -> str:
    copy = class_name

    copy = copy \
        .replace('final ', '') \
        .replace(' : ', ' derived from ') \
        .replace(' public ', ' ')

    tokens = copy.removeprefix('class ').split(' ')
    copy = ''
    for token in tokens:
        class_tokens = token.split('::')
        final_token: str = ''
        if len(class_tokens) > 1:
            for i in range(0, len(class_tokens) - 1):
                final_token += class_tokens[len(class_tokens) - i - 1] + ' nested in '
            final_token += class_tokens[0]

            copy += final_token + ' '

        else:
            copy += token + ' '

    return copy.replace(' derived from', ', derived from').strip()


def classes_in_string(string: str) -> [(str, str)]:
    class_texts: [(str, str)] = []

    for i in range(len(string)):
        if string[i:i + len('class')] == 'class':
            is_definition: bool = False
            bracket_count: int = 0
            end_index: int = 0
            first_bracket_index: int = -1
            last_bracket_index: int = -1

            for j in range(i, len(string)):
                end_index = j
                if string[j] == ';' and bracket_count == 0:
                    break
                elif string[j] == '{':
                    is_definition = True
                    bracket_count += 1

                    if first_bracket_index == -1:
                        first_bracket_index = j
                elif string[j] == '}':
                    bracket_count -= 1

                    last_bracket_index = j

            if is_definition:
                class_texts.append(
                    (norm_class_name(string[i:first_bracket_index]), string[first_bracket_index:last_bracket_index]))
                # print('----'*18)
                # print(f'{norm_class_name(string[i:first_bracket_index])} -> {string[first_bracket_index:end_index]}')

    # print(class_texts)
    return class_texts


class ClassFunction:

    def __init__(self):
        self.__comment: str = ''
        self.__head: str = ''
        self.__body: str = ''
        self.__parameters: [str] = []
        self.__modifiers: [str] = []
        self.__ret: str = ''

    @property
    def ret(self) -> str:
        return self.__ret

    @ret.setter
    def ret(self, value: str) -> None:
        self.__ret = value

    @property
    def modifiers(self) -> [str]:
        return self.__modifiers

    @modifiers.setter
    def modifiers(self, value: [str]) -> None:
        self.__modifiers = value

    @property
    def parameters(self) -> [str]:
        return self.__parameters

    @parameters.setter
    def parameters(self, value: [str]) -> None:
        self.__parameters = value

    @property
    def body(self) -> str:
        return self.__body

    @body.setter
    def body(self, value: str) -> None:
        self.__body = value

    @property
    def comment(self) -> str:
        return self.__comment

    @comment.setter
    def comment(self, value: str) -> None:
        self.__comment = value

    @property
    def head(self) -> str:
        return self.__head

    @head.setter
    def head(self, value: str) -> None:
        self.__head = value


class ClassBody:

    def __init__(self):
        self.__functions: ClassFunction = []

    @property
    def functions(self) -> [ClassFunction]:
        return self.__functions

    @functions.setter
    def functions(self, value: [ClassFunction]):
        self.__functions = value


def digest_class_body(class_body: str) -> ClassBody:
    # print(class_body)

    class_body = class_body.strip().removeprefix('{').removesuffix('}')
    print(class_body)

    skip_c = False

    body: ClassBody = ClassBody()
    for i in range(0, len(class_body)):
        if skip_c:
            if class_body[i] != '\n':
                continue
            else:
                skip_c = False
        if class_body[i:i+2] == '//':
            skip_c = True
            # while class_body[i] != '\n':
            #     i += 1
            # continue
        if class_body[i] == '(':
            print(i)
            is_def = False
            bracket_count = 0
            first_bracket_index = -1
            last_bracket_index = -1

            # print(class_body[i:])
            for j in range(i, len(class_body)):
                end_index = j
                if bracket_count == 0 and (class_body[j] == ';' or is_def):
                    last_bracket_index = j
                    break
                elif class_body[j] == '{':
                    is_def = True
                    bracket_count += 1

                    if first_bracket_index == -1:
                        first_bracket_index = j
                elif class_body[j] == '}':
                    bracket_count -= 1

                    last_bracket_index = j

            print('----' * 18, file=out_file)
            print(class_body[i: last_bracket_index], file=out_file)

    return body
    # return ClassBody()


def run_script() -> None:
    path_of_class: str = ''

    if len(argv) < 2:
        path_of_class = input('Enter the path of the classfile to check : ')
    else:
        path_of_class = argv[1]

    file_text = ''
    for line in open(path_of_class, 'r').readlines():
        file_text += line

    for class_title, class_body in classes_in_string(file_text):
        # print(class_title)
        digested_body = digest_class_body(class_body)

    # print(file_text)

    #
    # for class_text in re.findall(r'class[a-zA-Z0-9 \t\n\r]*{.*}', file_text):
    #     print(re.sub(r'constexpr', '', class_text))

    input('Press Enter to continue...')


if __name__ == '__main__':
    run_script()
