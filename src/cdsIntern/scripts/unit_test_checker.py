from sys import argv

out_file = open('log.txt', 'w')

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


def digest_class_body(class_body: str, class_id: str) -> ClassBody:
    # print(class_body)
    function_modifiers = ['constexpr', 'static', 'consteval', 'inline', 'noexcept', 'noexcept(false)',
                          'noexcept(true)', 'mutable', 'final', 'override', 'const', '[[nodiscard]]', '[[noreturn]]',
                          '[[maybe_unused]]', 'explicit', 'auto', 'virtual']

    class_body = class_body.strip().removeprefix('{').removesuffix('}')
    # print(class_body)

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
            if class_body[i:i+len('(false)')] == '(false)':
                continue
            # print(i)
            is_def = False
            bracket_count = 0
            first_bracket_index = -1
            last_bracket_index = -1

            # print(class_body[i:])
            for j in range(i, len(class_body)):
                last_bracket_index = j
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

            current_function: ClassFunction = ClassFunction()

            comment_text: str = class_body[class_body[:i].rfind('/**'): class_body[:i].rfind('*/') + 2].strip()
            head_text: str = class_body[class_body[:i].rfind('\n'):i].strip()
            parameter_text: str = class_body[i: i + class_body[i:].find(')')+1].strip()
            body_text = class_body[i + class_body[i:].find(')') + 1: last_bracket_index+1].strip()

            for modifier in function_modifiers:
                if modifier in head_text:
                    head_text = head_text.replace(modifier, '').strip()
                    current_function.modifiers.append(modifier)
                if modifier in parameter_text:
                    parameter_text = parameter_text.replace(modifier, '').strip()
                    current_function.modifiers.append(modifier)
                if modifier in body_text:
                    body_text = body_text.replace(modifier, '').strip()
                    current_function.modifiers.append(modifier)


            # print(body_text, file=out_file)
            if '->' in body_text:
                current_function.ret = body_text[body_text.find('->') + 2:body_text.find('{') if '{' in body_text else body_text.find(';')].strip()
                # body_text.replace()
            else:
                current_function.ret = head_text[0: head_text.find(' ') if ' ' in head_text.strip() else len(head_text)].strip()
                head_text = head_text[head_text.find(' ') + 1:]


            # print(comment_text, file=out_file)
            # print(head_text, file=out_file)
            # print(parameter_text, file=out_file)
            # print(body_text, file=out_file)

            current_function.body = body_text.strip()
            current_function.parameters = parameter_text.strip().removesuffix(')').removeprefix('(').split(',')
            current_function.comment = comment_text.strip()
            current_function.head = head_text.strip()

            if current_function.head == current_function.ret and '~' not in current_function.head:
                current_function.ret = ''
                current_function.head = 'Constructor'

            if '~' in current_function.head:
                current_function.ret = ''
                current_function.head = 'Destructor'

            if '{' in current_function.head:
                continue

            print('----' * 18, file=out_file)

            print(f'CLASS = {class_id}', file=out_file)
            print(f'COMMENT = {current_function.comment}', file=out_file)
            print(f'HEAD = {current_function.head}', file=out_file)
            print(f'PARAMETERS = {current_function.parameters}', file=out_file)
            print(f'MODIFIERS = {current_function.modifiers}', file=out_file)
            print(f'RETURN = {current_function.ret}', file=out_file)
            # print(f'BODY = {current_function.body}', file=out_file)

            body.functions.append(current_function)

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
        digested_class = digest_class_body(class_body, class_title)

        for f in digested_class.functions:
            if not f.comment:
                print(f'Warning: Function "{f.head}" ( in {class_title} ) does not have a comment indicating a testcase')
                print()
            elif '@test' not in f.comment:
                print(f'Warning: Function "{f.head}" ( in {class_title} ) does not have a test case attached in comment')
                print()

    # print(file_text)

    #
    # for class_text in re.findall(r'class[a-zA-Z0-9 \t\n\r]*{.*}', file_text):
    #     print(re.sub(r'constexpr', '', class_text))

    input('Press Enter to continue...')


if __name__ == '__main__':
    run_script()
