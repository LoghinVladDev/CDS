import re
from typing import Iterator

try:
    import gdb

    if hasattr(gdb, 'default_visualizer') and hasattr(gdb, 'write') and hasattr(gdb, 'pretty_printers')\
            and hasattr(gdb, 'TYPE_CODE_REF') and hasattr(gdb, 'TYPE_CODE_PTR') and hasattr(gdb, 'parse_and_eval'):
        default_visualizer = gdb.default_visualizer
        write = gdb.write
        pretty_printers = gdb.pretty_printers
        TYPE_CODE_REF = gdb.TYPE_CODE_REF
        TYPE_CODE_PTR = gdb.TYPE_CODE_PTR
        parse_and_eval = gdb.parse_and_eval
    else:
        raise ImportError()
except ImportError:
    default_visualizer = lambda x: x
    write = print
    pretty_printers = []
    TYPE_CODE_REF = 1
    TYPE_CODE_PTR = 2
    parse_and_eval = lambda x: x

display_names = {
    'BaseString': 'String'
}

nullptr = None
pvoid = None

def type_of(val):
    t = val.type
    if t.code == TYPE_CODE_REF:
        t = t.target()
    return t

def is_null(ptr):
    global nullptr
    global pvoid
    return ptr.cast(pvoid) == nullptr

def get_template_arg_list(type):
    n = 0
    template_args = []
    while True:
        try:
            template_args.append(type.template_argument(n))
        except:
            return template_args
        n += 1

def upcast_to_base(val, base_idx = 0):
    base_type = type_of(val).fields()[base_idx].type.strip_typedefs()
    return val.cast(base_type)

def strip_ns(name: str):
    return name.rsplit(':', 2)[-1]

def strip_targs(name: str):
    return name.split('<', 2)[0]

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
type_matcher = re.compile('^(?P<qual_name>cds::[^<]*)(?P<type_params><.*>)?(?P<ptr_quals>.+)?$')

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
        possible_types = get_template_arg_list(type_of(val))
        self.index = int(val['_index'])
        self.size = len(possible_types)
        contained_value = None
        visualizer = None
        self._contained_type = None
        if self.index < self.size:
            self.contained_type = possible_types[int(self.index)]
            if self.contained_type == gdb.lookup_type('std::nullptr_t'):
                contained_value = parse_and_eval('static_cast<std::nullptr_t>(0)')
            else:
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
            nodes = type_of(self.head).fields()
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
        types = get_template_arg_list(type_of(val))
        self.size = len(types)
        self.val = val
        super(TuplePrinter, self).__init__(quals, type_name, type_params)

    def children(self):
        return self.TupleIterator(self.val)

    def to_string(self):
        if self.size == 0:
            return '[empty tuple]'
        return f'[tuple of {self.size} values]'

class MapEntryPrinter(TuplePrinter):
    def __init__(self, quals, type_name, type_params, val):
        base_class_type = type_of(val).fields()[0].type
        as_tuple = val.cast(base_class_type)
        super(MapEntryPrinter, self).__init__(quals, type_name, type_params, as_tuple)

    def to_string(self):
        return f'[map entry]'

class ContiguousRangePrinter(TypePrinter):
    class ContiguousRangeIterator(Iterator):
        def __init__(self, head, tail):
            self.current = head
            self.tail = tail
            self.index = 0

        def __iter__(self):
            return self

        def __next__(self):
            index = self.index
            self.index += 1

            if self.current == self.tail:
                raise StopIteration
            value = self.current.dereference()
            self.current = self.current + 1
            return f'[{index}]', value

    def __init__(self, quals, type_name, type_params, head, tail):
        super(ContiguousRangePrinter, self).__init__(quals, type_name, type_params)
        self.head = head
        self.tail = tail

    def children(self):
        return self.ContiguousRangeIterator(self.head, self.tail)

class VectorPrinter(ContiguousRangePrinter):
    def __init__(self, quals, type_name, type_params, val):
        head = val['_head']
        tail = val['_tail']
        self.capacity = val['_cap']
        super(VectorPrinter, self).__init__(quals, type_name, type_params, head, tail)

    def to_string(self):
        return f'[length {int(self.tail - self.head)}, capacity {int(self.capacity)}]'

class VectorViewPrinter(ContiguousRangePrinter):
    def __init__(self, quals, type_name, type_params, val):
        size_max = parse_and_eval('static_cast<std::size_t>(-1)')
        if val.type.template_argument(1) == size_max:
            begin = val['_begin']
            end = val['_end']
        else:
            begin = val['_addr']
            end = begin + int(val.type.template_argument(1))
        super(VectorViewPrinter, self).__init__(quals, type_name, type_params, begin, end)

    def to_string(self):
        return f'[length {int(self.tail - self.head)}]'

class HashTablePrinter(TypePrinter):
    class HashTableIterator(Iterator):
        def __init__(self, head, tail):
            self.head = head
            self.tail = tail
            self.current = self.head.dereference()
            self.index = 0
            self.locate_next()

        def locate_next(self):
            if not is_null(self.current):
                self.current = self.current['next']

            if not is_null(self.current):
                return

            while self.head != self.tail:
                self.head += 1
                if self.head != self.tail:
                    self.current = self.head.dereference()
                    if not is_null(self.current):
                        return

        def __iter__(self):
            return self

        def __next__(self):
            if self.head == self.tail:
                raise StopIteration

            value = self.current['data']
            index = self.index
            self.index += 1
            self.locate_next()
            return f'[{index}]', value

    def __init__(self, quals, type_name, type_params, val):
        super(HashTablePrinter, self).__init__(quals, type_name, type_params)
        self.table = val['_bArr']
        self.bucket_count = val['_bCnt']
        self.size = val['_eCnt']

    def children(self):
        return self.HashTableIterator(self.table, self.table + self.bucket_count)

    def to_string(self):
        return f'[size {self.size}, bucket count {self.bucket_count}]'

class LinkedListPrinter(TypePrinter):
    class LinkedListIterator(Iterator):
        def __init__(self, current):
            self.current = current
            self.index = 0

        def __iter__(self):
            return self

        def __next__(self):
            if is_null(self.current):
                raise StopIteration

            index = self.index
            self.index += 1
            value = self.current['data']
            self.current = self.current['next']
            return f'[{index}]', value

    def __init__(self, quals, type_name, type_params, head):
        super(LinkedListPrinter, self).__init__(quals, type_name, type_params)
        self.head = head

    def children(self):
        return self.LinkedListIterator(self.head)

class LinkedHashTablePrinter(LinkedListPrinter):
    def __init__(self, quals, type_name, type_params, val):
        self.table = val['_bArr']
        self.bucket_count = val['_bCnt']
        self.size = val['_eCnt']
        head = val['_f']
        super(LinkedHashTablePrinter, self).__init__(quals, type_name, type_params, head)

    def to_string(self):
        return f'[size {self.size}, bucket count {self.bucket_count}]'

json_type_names = [
    "null",
    "bool",
    "long",
    "double",
    "string",
    "array",
    "object"
]

class JsonNodePrinter(UnionPrinter):
    def __init__(self, quals, type_name, type_params, val):
        fields = type_of(val).fields()
        if not fields:
            raise ValueError(f'Unexpected empty fields for value {val}, type {val.type}')

        while strip_ns(strip_targs(val.type.name)) != 'Union':
            val = upcast_to_base(val)

        super(JsonNodePrinter, self).__init__(quals, type_name, type_params, val)

    def children(self):
        if self.index < 5:
            return [].__iter__()
        return super(JsonNodePrinter, self).children()

    def to_string(self):
        if self.index == 0 or self.index >= self.size:
            return 'null'

        type_name = json_type_names[self.index]
        if self.index < 4:
            return f'{self.contained_value}'
        elif self.index == 4:
            return f'{self.contained_value.dereference()}'
        elif self.index == 5:
            val = self.contained_value.dereference()
            length = int(val['_tail'] - val['_head'])
            cap = val['_cap']
            additional = f', length {length}, capacity {cap}'
        elif self.index == 6:
            val = self.contained_value.dereference()
            size = val['_eCnt']
            bucket_count = val['_bCnt']
            additional = f', size {size}, bucket count {bucket_count}'
        else:
            raise ValueError()
        return f'[{type_name}{additional}]'

def extract_map_entry(val):
    base_tuple_type = val.type.fields()[0].type
    as_base_tuple = val.cast(base_tuple_type)
    base_node_type = as_base_tuple.type.fields()[0].type
    as_base_node = as_base_tuple.cast(base_node_type)
    key = as_base_node['_nodeData']
    next_node_type = as_base_node.type.fields()[0].type
    as_next_node = as_base_node.cast(next_node_type)
    value = as_next_node['_nodeData']
    return key, value

class JsonPrinter(TypePrinter):
    class JsonIterator(Iterator):
        def __init__(self, current):
            self.current = current
            self.index = 0

        def __iter__(self):
            return self

        def __next__(self):
            if is_null(self.current):
                raise StopIteration

            index = self.index
            self.index += 1
            key, value = extract_map_entry(self.current['data'])
            self.current = self.current['next']
            return f'[{key}]', value

    def __init__(self, quals, type_name, type_params, val):
        super(JsonPrinter, self).__init__(quals, type_name, type_params)
        self.table = val['_bArr']
        self.bucket_count = val['_bCnt']
        self.size = val['_eCnt']
        self.head = val['_f']

    def children(self):
        return self.JsonIterator(self.head)

    def to_string(self):
        return f'[size {self.size}, bucket count {self.bucket_count}]'

def register_pretty_printers():
    global printer_registry
    global nullptr
    global pvoid

    printer_registry = PrinterRegistry()
    nullptr = parse_and_eval('(void*)0')
    pvoid = gdb.lookup_type('void').const().pointer()

    printer_registry.register('cds::impl', 'BaseString', StringPrinter)
    printer_registry.register('cds::impl', 'BaseStringView', StringViewPrinter)

    printer_registry.register('cds', 'Optional', OptionalPrinter)
    printer_registry.register('cds::impl', 'Union', UnionPrinter)
    printer_registry.register('cds::impl', 'Tuple', TuplePrinter)

    printer_registry.register('cds::impl', 'Vector', VectorPrinter)
    printer_registry.register('cds::impl', 'BaseVector', VectorPrinter)
    printer_registry.register('cds::impl', 'VectorView', VectorViewPrinter)

    printer_registry.register('cds::impl', 'MapEntry', MapEntryPrinter)
    printer_registry.register('cds::impl', 'BaseHashMap', HashTablePrinter)
    printer_registry.register('cds::impl', 'HashMap', HashTablePrinter)
    printer_registry.register('cds::impl', 'BaseLinkedHashMap', LinkedHashTablePrinter)
    printer_registry.register('cds::impl', 'LinkedHashMap', LinkedHashTablePrinter)

    printer_registry.register('cds::json::impl', 'JsonNodeBase', JsonNodePrinter)
    printer_registry.register('cds::json::impl', 'JsonArrayBase', VectorPrinter)
    printer_registry.register('cds::json::impl', 'JsonObjectBase', JsonPrinter)

register_pretty_printers()
pretty_printers.append(printer_registry)
