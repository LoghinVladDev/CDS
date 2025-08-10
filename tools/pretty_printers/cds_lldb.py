# Installation:
#   - Via init file
#   - echo 'command script import "/path/to/cds/lldb/pretty/printer/cds_lldb.py"'

import typing
from abc import abstractmethod, ABC

try:
    import lldb
except ModuleNotFoundError:
    import lldb_typeinfo as lldb

logger: typing.Union[lldb.formatters.Logger.Logger, None] = None
global_byte_order = None

def log(v):
    global logger
    if logger is not None:
        logger.write(v)

def strip_ns(name: str):
    return name.rsplit(':', 2)[-1]

def strip_targs(name: str):
    return name.split('<', 2)[0]

def upcast(val: lldb.SBValue, base_idx = 0):
    the_type = remove_reference(val.GetType())
    base_cnt = the_type.GetNumberOfDirectBaseClasses()
    if base_idx >= base_cnt:
        raise IndexError()
    return val.GetChildAtIndex(base_idx)

def remove_reference(t: lldb.SBType) -> lldb.SBType:
    if t.IsReferenceType():
        return t.GetDereferencedType()
    return t

def upcast_until(val: lldb.SBValue, pred: typing.Callable[[lldb.SBValue], bool]) -> lldb.SBValue:
    if val.IsSynthetic():
        val = val.GetNonSyntheticValue()

    if pred(val):
        return val

    val_queue = [val]
    while val_queue:
        current = val_queue[0]
        val_queue = val_queue[1:]

        for class_idx in range(remove_reference(current.GetType()).GetNumberOfDirectBaseClasses()):
            as_base = upcast(current, class_idx)
            if as_base.IsValid():
                if pred(as_base):
                    return as_base
                val_queue.append(as_base)
    raise ValueError()

def value_type_name_checker(pred: typing.Callable[[str], bool]) -> typing.Callable[[lldb.SBValue], bool]:
    return lambda value: pred(strip_ns(strip_targs(remove_reference(value.GetType()).GetUnqualifiedType().GetName())))

def is_type_dereferenceable(t: lldb.SBType) -> bool:
    return t.IsPointerType() or t.IsReferenceType()

def is_value_dereferenceable(val: lldb.SBValue) -> bool:
    return is_type_dereferenceable(val.GetType())

def locate_value(val: lldb.SBValue) -> typing.Union[lldb.SBValue, None]:
    if val.IsSynthetic():
        val = val.GetNonSyntheticValue()

    if not val.IsValid():
        return None

    if is_value_dereferenceable(val):
        val = val.Dereference()

    return val

def clone(val: lldb.SBValue, name: str = '') -> lldb.SBValue:
    return val.CreateValueFromData(name, val.GetData(), val.GetType())

class ValuePrinter(ABC):
    def __init__(self, val: lldb.SBValue):
        self.val = locate_value(val)

    @abstractmethod
    def summary(self):
        ...

    def out(self):
        if self.val is not None:
            return self.summary()
        return 'summary unavailable'

class StringValuePrinter:
    def __init__(self, ptr, length: int):
        self.length = length
        self.ptr = ptr
        self.data = ''
        for b in self.ptr.uint8:
            if b == 0:
                self.data += '\\\\0'
            if chr(b) == '"' or chr(b) == '\\':
                self.data += '\\' + chr(b)
            else:
                self.data += chr(b)

    def summary(self):
        return f'"{self.data}"'

class StringPrinter(ValuePrinter, StringValuePrinter):
    def __init__(self, val: lldb.SBValue):
        ValuePrinter.__init__(self, val)
        if self.val is None:
            return

        string_data = upcast_until(self.val, value_type_name_checker(lambda name: name == 'StringData'))
        sbo = string_data.GetChildMemberWithName('_sbo')
        nrm = string_data.GetChildMemberWithName('_nrm')
        self.is_sbo = sbo.GetChildMemberWithName('lenSbo').GetData().uint8[0] & 1 != 0
        control = sbo if self.is_sbo else nrm
        buf = control.GetChildMemberWithName('buf')
        length = control.GetChildMemberWithName('lenSbo').GetValueAsUnsigned() >> 1
        ptr = buf.GetPointeeData(0, length)
        StringValuePrinter.__init__(self, ptr, length)

    def summary(self):
        return StringValuePrinter.summary(self)

class StringViewPrinter(ValuePrinter, StringValuePrinter):
    def __init__(self, val: lldb.SBValue):
        ValuePrinter.__init__(self, val)
        if self.val is None:
            return

        length = self.val.GetChildMemberWithName('_length').GetValueAsUnsigned()
        ptr = self.val.GetChildMemberWithName('_data').GetPointeeData(0, length)
        StringValuePrinter.__init__(self, ptr, length)

    def summary(self):
        return StringValuePrinter.summary(self)

class SingleObjectContainerPrinter(ValuePrinter, ABC):
    def __init__(self, val: lldb.SBValue):
        super(SingleObjectContainerPrinter, self).__init__(val)
        if self.val is None:
            return
        self.contained_value = None

    def update(self):
        self.contained_value = self.get_contained_value()
        # new_value = self.get_contained_value()
        # self.contained_value = clone(new_value, '[contained value]') if new_value else new_value
        return False

    def has_children(self):
        return self.contained_value is not None

    def num_children(self, _max_children):
        return 1 if self.contained_value else 0

    def get_child_index(self, name):
        return 0 if name == '[0]' else -1

    def get_child_at_index(self, index):
        return self.contained_value if self.contained_value is not None and index == 0 else None

    def summary(self):
        if self.contained_value:
            return self.summary_containing_value()
        return self.summary_without_value()

    def summary_containing_value(self):
        return '[containing value]'

    def summary_without_value(self):
        return '[no contained value]'

    @abstractmethod
    def get_contained_value(self) -> typing.Union[lldb.SBValue, None]:
        ...

class OptionalPrinter(SingleObjectContainerPrinter):
    def __init__(self, val: lldb.SBValue, _dict = None):
        super(OptionalPrinter, self).__init__(val)
        if self.val is None:
            return
        self.old_value = None

    def get_contained_value(self):
        if self.old_value is not None and not self.val.changed and not self.old_value.changed:
            return self.old_value
        opt_value = upcast_until(self.val, value_type_name_checker(lambda name: name == 'OptionalStorageBase'))
        initialized = bool(opt_value.GetChildMemberWithName('_exists').GetValueAsUnsigned())
        if not initialized:
            return None
        self.old_value = opt_value.GetChildMemberWithName('_object')
        return self.old_value.CreateChildAtOffset('[contained value]', 0, self.old_value.GetType())

class UnionPrinter(SingleObjectContainerPrinter):
    def __init__(self, val: lldb.SBValue, _dict = None):
        super(UnionPrinter, self).__init__(val)
        if self.val is None:
            return
        self.size = self.val.GetType().GetNumberOfTemplateArguments()
        self.index = self.size

    def obtain_current_value(self):
        if self.val is None:
            return None
        self.index = self.val.GetChildMemberWithName('_index').GetValueAsUnsigned()
        current_type = self.val.GetType().GetTemplateArgumentType(self.index)
        if self.index >= self.size:
            return None
        # addr_of_object = self.val.GetValueForExpressionPath('._data._head').AddressOf()
        # current_type_ptr = current_type.GetPointerType()
        # addr_casted = addr_of_object.Cast(current_type_ptr)
        # return addr_casted.Dereference()
        return (self.val.GetChildMemberWithName('_data').GetChildMemberWithName('_head')
                .CreateChildAtOffset('[contained value]', 0, current_type))

    def get_contained_value(self):
        return self.obtain_current_value()

    def summary_containing_value(self):
        return f'[index {self.index}]'

class TuplePrinter(ValuePrinter):
    def __init__(self, val: lldb.SBValue, _dict = None):
        super(TuplePrinter, self).__init__(val)
        if self.val is None:
            return
        self.tuple_val = upcast_until(self.val, value_type_name_checker(lambda name: name == 'Tuple'))
        self.size = remove_reference(self.tuple_val.GetType()).GetNumberOfTemplateArguments()
        self.types = self.tuple_val.GetType().template_args
        self.root_node = upcast_until(self.tuple_val, value_type_name_checker(lambda name: name == 'FwdTupleNode'))
        self.align = self.tuple_val.GetType().GetByteAlign()

    def has_children(self):
        return self.size != 0

    def update(self):
        return False

    def num_children(self, _max_children):
        return self.size

    def get_child_index(self, name: str):
        if name[0] != '[' or name[-1] != ']':
            return -1
        return int(name[1:-1])

    def get_child_at_index(self, index):
        offset = sum([max(e.GetByteSize(), self.align) for e in self.types[:index]])
        return self.val.CreateChildAtOffset(f'[{index}]', offset, self.types[index])

    def summary(self):
        if self.size == 0:
            return '[empty tuple]'
        return f'[tuple of {self.size} value{"s" if self.size > 1 else ""}]'

class ExpectedPrinter(SingleObjectContainerPrinter):
    STATE_UNINITIALIZED = 0
    STATE_VALUE = 1
    STATE_ERROR = 2

    def __init__(self, val: lldb.SBValue, _dict = None):
        super(ExpectedPrinter, self).__init__(val)
        if self.val is None:
            return
        self.value_type = self.val.GetType().GetTemplateArgumentType(0)
        self.error_type = self.val.GetType().GetTemplateArgumentType(1)
        self.state = ExpectedPrinter.STATE_UNINITIALIZED

    def get_contained_value(self) -> typing.Union[lldb.SBValue, None]:
        if self.val is None:
            return None
        self.state = self.val.GetChildMemberWithName('_state').GetValueAsUnsigned()
        data = self.val.GetChildMemberWithName('_data')
        if self.state == ExpectedPrinter.STATE_UNINITIALIZED:
            return None
        if self.state == ExpectedPrinter.STATE_VALUE:
            return (data.GetChildMemberWithName('value')
                    .CreateChildAtOffset('[value]', 0, self.value_type))
        if self.state == ExpectedPrinter.STATE_ERROR:
            return (data.GetChildMemberWithName('error')
                    .CreateChildAtOffset('[unexpected]', 0, self.error_type))
        raise ValueError(f'Invalid Expected State {self.state}')

    def summary_containing_value(self):
        if self.state == ExpectedPrinter.STATE_VALUE:
            return '[containing value]'
        if self.state == ExpectedPrinter.STATE_ERROR:
            return '[containing unexpected]'
        raise ValueError(f'Invalid Expected State {self.state}')

    def summary_without_value(self):
        return '[uninitialized]'

class ContiguousRangePrinter(ValuePrinter, ABC):
    def __init__(self, val: lldb.SBValue):
        super(ContiguousRangePrinter, self).__init__(val)
        self.head: typing.Union[lldb.SBValue, None] = None
        self.tail: typing.Union[lldb.SBValue, None] = None
        self.element_size: int = 0

    @abstractmethod
    def get_head_tail_element_size(self) -> typing.Tuple[lldb.SBValue, lldb.SBValue, int]:
        ...

    def update(self):
        if self.val is None:
            return False
        if self.head is not None and not self.val.changed:
            return False

        (self.head, self.tail, self.element_size) = self.get_head_tail_element_size()
        return False

    def num_children(self, max_children = None):
        current = (self.tail.GetValueAsUnsigned() - self.head.GetValueAsUnsigned()) // self.element_size
        if max_children is None:
            return current
        return min(current, max_children)

    def has_children(self) -> bool:
        return self.head.GetValueAsUnsigned() != self.tail.GetValueAsUnsigned()

    def get_child_index(self, name: str):
        if name[0] != '[' or name[-1] != ']':
            return -1
        return int(name[1:-1])

    def get_child_at_index(self, index):
        return self.head.CreateValueFromData(f'[{index}]', self.head.GetPointeeData(index), self.head.GetType().GetPointeeType())

class VectorPrinter(ContiguousRangePrinter):
    possible_base_classes = [
        'ArrayDynamicBackScalingBase'
    ]

    def as_base(self) -> lldb.SBValue:
        return upcast_until(self.val, value_type_name_checker(lambda name: name in VectorPrinter.possible_base_classes))

    def __init__(self, val: lldb.SBValue, _dict = None):
        super(VectorPrinter, self).__init__(val)
        self.initialized = False
        self.capacity = 0

    def get_head_tail_element_size(self) -> typing.Tuple[lldb.SBValue, lldb.SBValue, int]:
        as_base = self.as_base()
        head = as_base.GetChildMemberWithName('_head')
        tail = as_base.GetChildMemberWithName('_tail')
        element_size = head.GetType().GetPointeeType().GetByteSize()
        return head, tail, element_size

    def update(self):
        super().update()
        if not self.val:
            return False

        if self.val.changed or not self.initialized:
            self.capacity = self.as_base().GetChildMemberWithName('_cap').GetValueAsUnsigned()
            self.initialized = True
        return False

    def summary(self):
        return f'[length {self.num_children()}, capacity {self.capacity}]'

class VectorViewPrinter(ContiguousRangePrinter):
    possible_base_classes = [
        'BaseDynamicVectorView',
        'BaseStaticVectorView'
    ]

    def as_base(self) -> lldb.SBValue:
        return upcast_until(self.val, value_type_name_checker(
            lambda name: name in VectorViewPrinter.possible_base_classes))

    def __init__(self, val: lldb.SBValue, _dict = None):
        super(VectorViewPrinter, self).__init__(val)

    def get_head_tail_element_size(self) -> typing.Tuple[lldb.SBValue, lldb.SBValue, int]:
        as_base = self.as_base()
        full_type_name = as_base.GetType().GetName()
        if strip_ns(strip_targs(full_type_name)) == 'BaseStaticVectorView':
            head = as_base.GetChildMemberWithName('_addr')
            length = int(full_type_name.rsplit(',', 2)[-1].strip()[:-1].strip())
            element_size = head.GetType().GetPointeeType().GetByteSize()
            tail = as_base.CreateValueFromData('_tail', lldb.SBData.CreateDataFromUInt64Array(
                head.GetData().GetByteOrder(),
                head.GetType().GetByteSize(),
                [head.GetValueAsUnsigned() + length * element_size]
            ), head.GetType())
        else:
            head = as_base.GetChildMemberWithName('_begin')
            tail = as_base.GetChildMemberWithName('_end')
            element_size = head.GetType().GetPointeeType().GetByteSize()
        return head, tail, element_size

    def summary(self):
        return f'[length {self.num_children()}]'

    def update(self):
        super().update()
        return False

class MapEntryPrinter(TuplePrinter):
    def __init__(self, val: lldb.SBValue, _dict = None):
        super(MapEntryPrinter, self).__init__(val)

    def summary(self):
        return '[map entry]'

class HashTablePrinter(ValuePrinter):
    def __init__(self, val: lldb.SBValue, _dict = None):
        super(HashTablePrinter, self).__init__(val)
        self.nodes = []
        self.element_count = 0
        self.bucket_count = 0
        self.initialized = False

    def update(self):
        if self.val is None:
            return False

        if self.initialized and not self.val.changed:
            return False

        self.initialized = True
        val = upcast_until(self.val, value_type_name_checker(lambda name: name == 'HashTableBase'))
        table = val.GetChildMemberWithName('_bArr')
        self.element_count = val.GetChildMemberWithName('_eCnt').GetValueAsUnsigned()
        self.bucket_count = val.GetChildMemberWithName('_bCnt').GetValueAsUnsigned()
        self.nodes = []
        for b_idx in range(self.bucket_count):
            buck_data = table.GetPointeeData(b_idx)
            head_ptr = table.CreateValueFromData(f'bucket {b_idx}', buck_data, table.GetType().GetPointeeType())
            while head_ptr.GetValueAsUnsigned() != 0:
                head = head_ptr.Dereference()
                self.nodes.append(clone(head.GetChildMemberWithName('data'), f'[{len(self.nodes)}]'))
                head_ptr = head.GetChildMemberWithName('next')

        return False

    def summary(self):
        return f'[size {self.element_count}, bucket count {self.bucket_count}]'

    def has_children(self):
        return self.num_children() != 0

    def num_children(self, max_children = None):
        if max_children is None:
            return self.element_count
        return min(self.element_count, max_children)

    def get_child_index(self, name: str):
        if name[0] != '[' or name[-1] != ']':
            return -1
        return int(name[1:-1])

    def get_child_at_index(self, index):
        return self.nodes[index]

class LinkedHashTablePrinter(ValuePrinter):
    def __init__(self, val: lldb.SBValue, _dict = None):
        super(LinkedHashTablePrinter, self).__init__(val)
        self.nodes = []
        self.element_count = 0
        self.bucket_count = 0
        self.initialized = False

    def update(self):
        if self.val is None:
            return False

        if self.initialized and not self.val.changed:
            return False

        self.initialized = True
        sll_base = upcast_until(self.val, value_type_name_checker(lambda name: name == 'SingleLinkedListBase'))
        table_base = upcast_until(self.val, value_type_name_checker(lambda name: name == 'HashTableBase'))
        head_ptr = sll_base.GetChildMemberWithName('_f')
        self.element_count = table_base.GetChildMemberWithName('_eCnt').GetValueAsUnsigned()
        self.bucket_count = table_base.GetChildMemberWithName('_bCnt').GetValueAsUnsigned()
        self.nodes = []
        while head_ptr.GetValueAsUnsigned() != 0:
            head = head_ptr.Dereference()
            self.nodes.append(self.process_child(head.GetChildMemberWithName('data')))
            head_ptr = head.GetChildMemberWithName('next')

        return False

    def process_child(self, origin_val: lldb.SBValue) -> lldb.SBValue:
        return clone(origin_val, f'[{len(self.nodes)}]')

    def summary(self):
        return f'[size {self.element_count}, bucket count {self.bucket_count}]'

    def has_children(self):
        return self.num_children() != 0

    def num_children(self, max_children = None):
        if max_children is None:
            return self.element_count
        return min(self.element_count, max_children)

    def get_child_index(self, name: str):
        if name[0] != '[' or name[-1] != ']':
            return -1
        return int(name[1:-1])

    def get_child_at_index(self, index):
        return self.nodes[index]
    
class JsonNodePrinter(UnionPrinter):
    def __init__(self, val: lldb.SBValue, _dict = None):
        super(JsonNodePrinter, self).__init__(upcast_until(locate_value(val), value_type_name_checker(lambda name: name == 'Union')))
        self.active_printer = None
        self.actual_contained = None
        
    def get_contained_value(self):
        self.actual_contained = super().obtain_current_value()

        if self.index >= 4:
            self.actual_contained = self.actual_contained.Dereference()

        if self.index < 5:
            return None
        self.active_printer = (VectorPrinter(self.actual_contained) if self.index == 5 else
            JsonPrinter(self.actual_contained))
        self.active_printer.update()
        return self.actual_contained

    def summary_without_value(self):
        value = self.actual_contained
        if self.index == 0:
            return 'null'
        elif self.index == 1:
            return 'true' if value.GetValueAsUnsigned() != 0 else 'false'
        elif self.index == 2:
            return value.GetValueAsSigned()
        elif self.index == 3:
            return value.GetData().double[0]
        elif self.index == 4:
            return f'{StringPrinter(value).summary()}'
        else:
            raise ValueError()

    def has_children(self):
        if self.active_printer is None:
            return False
        return self.active_printer.has_children()

    def num_children(self, max_children):
        if self.active_printer is None:
            return 0
        return self.active_printer.num_children(max_children)

    def get_child_index(self, name):
        if self.active_printer is None:
            return -1
        return self.active_printer.get_child_index(name)

    def get_child_at_index(self, index):
        if self.active_printer is None:
            return None
        child = self.active_printer.get_child_at_index(index)
        return child

    def summary_containing_value(self):
        if self.index == 5:
            return f'[array, length {self.active_printer.num_children()}, capacity {self.active_printer.capacity}]'
        elif self.index == 6:
            return f'[object, size {self.active_printer.element_count}, bucket count {self.active_printer.bucket_count}]'
        raise ValueError(f'{self.index}')

class JsonPrinter(LinkedHashTablePrinter):
    def __init__(self, val: lldb.SBValue, _dict = None):
        super(JsonPrinter, self).__init__(val)

    def process_child(self, val: lldb.SBValue) -> lldb.SBValue:
        entry_printer = MapEntryPrinter(val)
        key_printer = StringPrinter(entry_printer.get_child_at_index(0))
        return clone(entry_printer.get_child_at_index(1), f'[{key_printer.summary()}]')

def string_summary(val, _dict):
    return StringPrinter(val).out()

def string_view_summary(val, _dict):
    return StringViewPrinter(val).out()

def optional_summary(val, _dict):
    printer = OptionalPrinter(val)
    printer.update()
    return printer.out()

def union_summary(val, _dict):
    printer = UnionPrinter(val)
    printer.update()
    return printer.out()

def tuple_summary(val, _dict):
    printer = TuplePrinter(val)
    printer.update()
    return printer.out()

def expected_summary(val, _dict):
    printer = ExpectedPrinter(val)
    printer.update()
    return printer.out()

def vector_summary(val, _dict):
    printer = VectorPrinter(val)
    printer.update()
    return printer.out()

def vector_view_summary(val, _dict):
    printer = VectorViewPrinter(val)
    printer.update()
    return printer.out()

def map_entry_summary(val, _dict):
    printer = MapEntryPrinter(val)
    printer.update()
    return printer.out()

def hash_table_summary(val, _dict):
    printer = HashTablePrinter(val)
    printer.update()
    return printer.out()

def linked_hash_table_summary(val, _dict):
    printer = LinkedHashTablePrinter(val)
    printer.update()
    return printer.out()

def json_node_summary(val, _dict):
    printer = JsonNodePrinter(val)
    printer.update()
    return printer.out()

def json_summary(val, _dict):
    printer = JsonPrinter(val)
    printer.update()
    return printer.out()

class NoChildProvider:
    def __init__(self, _1, _2):
        pass

    def has_children(self):
        return False

logging_enabled = False

def __lldb_init_module(debugger, _):
    global logging_enabled
    global logger
    global global_byte_order

    global_byte_order = debugger.GetSelectedTarget().GetByteOrder()

    if logging_enabled:
        lldb.formatters.Logger._lldb_formatters_debug_level = 2
        logger = lldb.formatters.Logger.Logger()

    def register_printer(ns: str, name: str, summarizer: str, child_provider: str):
        cvqual = '((const|volatile) )?'
        debugger.HandleCommand(
            f'type summary add -x \"^{cvqual}{ns}::{name}(<.*>)?{cvqual}([^a-zA-Z:]*)?$\" -F cds_lldb.{summarizer} -w cds'
        ), debugger.HandleCommand(
            f'type synthetic add -x \"^{cvqual}{ns}::{name}(<.*>)?{cvqual}([^a-zA-Z:]*)?$\" --python-class cds_lldb.{child_provider} -w cds'
        )

    register_printer('cds::impl', 'BaseString', 'string_summary', 'NoChildProvider')
    register_printer('cds::impl', 'BaseStringView', 'string_view_summary', 'NoChildProvider')

    register_printer('cds', 'Optional', 'optional_summary', 'OptionalPrinter')
    register_printer('cds::impl', 'Union', 'union_summary', 'UnionPrinter')
    register_printer('cds::impl', 'Tuple', 'tuple_summary', 'TuplePrinter')
    register_printer('cds::impl', 'Expected', 'expected_summary', 'ExpectedPrinter')

    register_printer('cds::impl', 'Vector', 'vector_summary', 'VectorPrinter')
    register_printer('cds::impl', 'BaseVector', 'vector_summary', 'VectorPrinter')
    register_printer('cds::impl', 'VectorView', 'vector_view_summary', 'VectorViewPrinter')

    register_printer('cds::impl', 'MapEntry', 'map_entry_summary', 'MapEntryPrinter')
    register_printer('cds::impl', 'BaseHashMap', 'hash_table_summary', 'HashTablePrinter')
    register_printer('cds::impl', 'HashMap', 'hash_table_summary', 'HashTablePrinter')
    register_printer('cds::impl', 'BaseLinkedHashMap', 'linked_hash_table_summary', 'LinkedHashTablePrinter')
    register_printer('cds::impl', 'LinkedHashMap', 'linked_hash_table_summary', 'LinkedHashTablePrinter')
    
    register_printer('cds::json::impl', 'JsonNodeBase', 'json_node_summary', 'JsonNodePrinter')
    register_printer('cds::json::impl', 'JsonArrayBase', 'vector_summary', 'VectorPrinter')
    register_printer('cds::json::impl', 'JsonObjectBase', 'json_summary', 'JsonPrinter')

    debugger.HandleCommand('type category enable cds')
