import re
from typing import Iterator

try:
    import gdb

    if hasattr(gdb, 'default_visualizer') and hasattr(gdb, 'write') and hasattr(gdb, 'pretty_printers')\
            and hasattr(gdb, 'TYPE_CODE_REF') and hasattr(gdb, 'TYPE_CODE_PTR'):
        default_visualizer = gdb.default_visualizer
        write = gdb.write
        pretty_printers = gdb.pretty_printers
        TYPE_CODE_REF = gdb.TYPE_CODE_REF
        TYPE_CODE_PTR = gdb.TYPE_CODE_PTR
    else:
        raise ImportError()
except ImportError:
    default_visualizer = lambda x: x
    write = print
    pretty_printers = []
    TYPE_CODE_REF = 1
    TYPE_CODE_PTR = 2

display_names = {
    'BaseString': 'String'
}

def get_template_arg_list(type):
    n = 0
    template_args = []
    while True:
        try:
            template_args.append(type.template_argument(n))
        except:
            return template_args
        n += 1

class TypePrinter(object):
    def __init__(self, quals, type_name: str, type_params):
        self.quals = quals
        self.actual_type_name: str = type_name
        self.type_name = display_names[type_name] if type_name in display_names else type_name
        self.type_params: str = type_params if type_params else ''

class SingleObjectContainerPrinter(TypePrinter):
    def __init__(self, quals, type_name, type_params, value, visualizer):
        super(SingleObjectContainerPrinter, self).__init__(quals, type_name, type_params)
        self.contained_value = value
        self.visualizer = visualizer

    class IterContained(Iterator):
        def __init__(self, val):
            self.val = val

        def __iter__(self):
            return self

        def __next__(self):
            if self.val is None:
                raise StopIteration
            r = self.val
            self.val = None
            return '[contained_value]', r

    def children(self):
        if self.contained_value is None:
            return self.IterContained(None)
        if hasattr(self.visualizer, 'children'):
            return self.visualizer.children()
        return self.IterContained(self.contained_value)

printer_registry = None

split_by = re.compile(r'::')
type_matcher = re.compile('^(?P<qual_name>cds::[^<]*)(?P<type_params><.*>)?(?P<ptr_quals>[^>]+)?$')

class PrinterRegistry:
    def __init__(self):
        self.printers = {}
        pass

    def register(self, ns_qual: str, type_name: str, printer: type):
        ns_qual_bits = split_by.split(ns_qual)
        current_p_subset = self.printers
        for bit in ns_qual_bits:
            if bit not in current_p_subset:
                current_p_subset[bit] = {}
            current_p_subset = current_p_subset[bit]
        current_p_subset[type_name] = printer

    def __call__(self, val):
        t_type = val.type.strip_typedefs()

        if t_type.code == TYPE_CODE_REF:
            t_type = t_type.target()

        # deref_cnt = 0
        # d_val = val
        # while t_type and t_type.code == TYPE_CODE_PTR and (str(t_type.unqualified()) != 'void *'):
        #     d_val = d_val.dereference()
        #     t_type = d_val.type
        #     print(str(t_type))
        #     deref_cnt += 1

        match = type_matcher.fullmatch(str(t_type.name))
        if not match:
            return None

        qual_name = match['qual_name']
        type_params = match['type_params']

        qual_bits = split_by.split(qual_name)
        type_name = qual_bits[-1]

        subset = self.printers
        for bit in qual_bits:
            if not hasattr(subset, '__getitem__'):
                return None
            if bit in subset:
                subset = subset[bit]
            else:
                return None

        if not callable(subset):
            return None
        return subset(qual_bits[:-1], type_name, type_params, val)

class StringValuePrinter(TypePrinter):
    def __init__(self, quals, type_name, type_params, data, length):
        super(StringValuePrinter, self).__init__(quals, type_name, type_params)
        self.length = length
        self.ptr = data
        self.str = self.ptr.string(length=self.length)

    def to_string(self):
        return f'"{self.str}"'

class StringPrinter(StringValuePrinter):
    def __init__(self, quals, type_name, type_params, val):
        sbo = val['_sbo']
        nrm = val['_nrm']
        is_sbo = (sbo['lenSbo'] & 1) != 0

        self.is_sbo = is_sbo
        ptr = sbo['buf'] if self.is_sbo else nrm['buf']
        length = int(sbo['lenSbo'] if self.is_sbo else nrm['lenSbo']) >> 1
        super(StringPrinter, self).__init__(quals, type_name, type_params, ptr, length)

class StringViewPrinter(StringValuePrinter):
    def __init__(self, quals, type_name, type_params, val):
        ptr = val['_data']
        length = val['_length']
        super(StringViewPrinter, self).__init__(quals, type_name, type_params, ptr, length)

class OptionalPrinter(SingleObjectContainerPrinter):
    def __init__(self, quals, type_name, type_params, val):
        initialized = bool(val['_exists'])
        if not initialized:
            visualizer = None
            contained_value = None
        else:
            contained_value = val['_object']
            visualizer = default_visualizer(contained_value)
        super(OptionalPrinter, self).__init__(quals, type_name, type_params, contained_value, visualizer)

    def to_string(self):
        if not self.contained_value:
            return f'[no contained value]'
        if hasattr(self.visualizer, 'children'):
            return f'{self.type_name} containing {self.visualizer.to_string()}'
        return f'[containing value]'

class UnionPrinter(SingleObjectContainerPrinter):
    def __init__(self, quals, type_name, type_params, val):
        possible_types = get_template_arg_list(val.type)
        self.index = int(val['_index'])
        contained_value = None
        visualizer = None
        self._contained_type = None
        if self.index < len(possible_types):
            self.contained_type = possible_types[int(self.index)]
            addr = val['_data']['_head'].address
            contained_value = addr.cast(self.contained_type.pointer()).dereference()
            visualizer = default_visualizer(contained_value)
        super(UnionPrinter, self).__init__(quals, type_name, type_params, contained_value, visualizer)

    def to_string(self):
        if not self.contained_value:
            return f'[no contained value]'
        if hasattr(self.visualizer, 'children'):
            return f'[index {self.index}] containing {self.visualizer.to_string()}'
        return f'[index {self.index}]'

class TuplePrinter(TypePrinter):
    class TupleIterator(Iterator):
        @staticmethod
        def is_nonempty(nodes):
            return len(nodes) > 0

        def __init__(self, head):
            self.head = head
            nodes = self.head.type.fields()
            if self.is_nonempty(nodes):
                self.head = self.head.cast(nodes[0].type)
            self.index = 0

        def __iter__(self):
            return self

        def __next__(self):
            nodes = self.head.type.fields()

            if len(nodes) == 0:
                raise StopIteration

            if len(nodes) != 2:
                raise ValueError()

            value = self.head['_nodeData']
            self.head = self.head.cast(nodes[0].type)
            self.index += 1
            return f'[{self.index - 1}]', value

    def __init__(self, quals, type_name, type_params, val):
        types = get_template_arg_list(val.type)
        self.size = len(types)
        self.val = val
        super(TuplePrinter, self).__init__(quals, type_name, type_params)

    def children(self):
        return self.TupleIterator(self.val)

    def to_string(self):
        if self.size == 0:
            return '[empty tuple]'
        return f'[tuple of {self.size} values]'

def register_pretty_printers():
    global printer_registry
    printer_registry = PrinterRegistry()

    printer_registry.register('cds::impl', 'BaseString', StringPrinter)
    printer_registry.register('cds::impl', 'BaseStringView', StringViewPrinter)

    printer_registry.register('cds', 'Optional', OptionalPrinter)
    printer_registry.register('cds::impl', 'Union', UnionPrinter)
    printer_registry.register('cds::impl', 'Tuple', TuplePrinter)

register_pretty_printers()
pretty_printers.append(printer_registry)
