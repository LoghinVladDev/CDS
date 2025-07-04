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
    the_type = val.GetType()
    base_type = the_type.GetDirectBaseClassAtIndex(base_idx).GetType()
    return val.Cast(base_type)

def upcast_until(val: lldb.SBValue, pred: typing.Callable[[lldb.SBValue], bool]) -> lldb.SBValue:
    if pred(val):
        return val

    val_queue = [val]
    while val_queue:
        current = val_queue[0]
        val_queue = val_queue[1:]

        for class_idx in range(current.GetType().GetNumberOfDirectBaseClasses()):
            as_base = upcast(current, class_idx)
            if as_base.IsValid():
                if pred(as_base):
                    return as_base
                val_queue.append(as_base)
    raise ValueError()

class ValuePrinter(ABC):
    def __init__(self, val: lldb.SBValue):
        self.val = val
        if self.val.IsSynthetic():
            self.val = self.val.GetNonSyntheticValue()

        if not self.val.IsValid():
            self.val = None
            return

        if self.val.GetType().IsPointerType():
            self.val = self.val.Dereference()

    @abstractmethod
    def to_string(self):
        ...

    def out(self):
        if self.val is not None:
            return self.to_string()
        return 'summary unavailable'

class StringValuePrinter:
    def __init__(self, ptr, length: int):
        self.length = length
        self.ptr = ptr
        self.data = ''
        for b in self.ptr.uint8:
            if b == 0:
                self.data += '\\\\0'
            else:
                self.data += chr(b)

    def to_string(self):
        return f'"{self.data}"'

class StringPrinter(ValuePrinter, StringValuePrinter):
    def __init__(self, val: lldb.SBValue):
        ValuePrinter.__init__(self, val)
        if self.val is None:
            return

        string_data = upcast_until(self.val, lambda value: strip_ns(strip_targs(value.GetType().GetName())) == 'StringData')
        sbo = string_data.GetValueForExpressionPath('._sbo')
        nrm = string_data.GetValueForExpressionPath('._nrm')
        self.is_sbo = sbo.GetValueForExpressionPath('.lenSbo').GetData().uint8[0] & 1 != 0
        control = sbo if self.is_sbo else nrm
        buf = control.GetValueForExpressionPath('.buf')
        length = control.GetValueForExpressionPath('.lenSbo').GetValueAsUnsigned() >> 1
        ptr = buf.GetPointeeData(0, length)
        StringValuePrinter.__init__(self, ptr, length)

    def to_string(self):
        return StringValuePrinter.to_string(self)

class StringViewPrinter(ValuePrinter, StringValuePrinter):
    def __init__(self, val: lldb.SBValue):
        ValuePrinter.__init__(self, val)
        if self.val is None:
            return

        length = self.val.GetValueForExpressionPath('._length').GetValueAsUnsigned()
        ptr = self.val.GetValueForExpressionPath('._data').GetPointeeData(0, length)
        StringValuePrinter.__init__(self, ptr, length)

    def to_string(self):
        return StringValuePrinter.to_string(self)

class SingleObjectContainerPrinter(ValuePrinter, ABC):
    def __init__(self, val: lldb.SBValue):
        super(SingleObjectContainerPrinter, self).__init__(val)
        if self.val is None:
            return
        self.contained_value = None

    def update(self):
        new_value = self.get_contained_value()
        self.contained_value = new_value.Clone('[contained value]') if new_value else new_value
        return self

    def has_children(self):
        return self.contained_value is not None

    def num_children(self, _max_children):
        return 1 if self.contained_value else 0

    def get_child_index(self, name):
        return 0 if name == '[0]' else -1

    def get_child_at_index(self, index):
        return self.contained_value if self.contained_value is not None and index == 0 else None

    def to_string(self):
        if self.contained_value:
            return f'[{self.summary_containing_value()}]'
        return '[no contained value]'

    def summary_containing_value(self):
        return 'containing value'

    @abstractmethod
    def get_contained_value(self) -> typing.Union[lldb.SBValue, None]:
        ...

class OptionalPrinter(SingleObjectContainerPrinter):
    def __init__(self, val: lldb.SBValue, _dict = None):
        super(OptionalPrinter, self).__init__(val)
        if self.val is None:
            return

    def get_contained_value(self):
        opt_value = upcast_until(self.val, lambda value: strip_ns(strip_targs(value.GetType().GetName())) == 'OptionalStorageBase')
        initialized = bool(opt_value.GetValueForExpressionPath('._exists').GetValueAsUnsigned())
        if not initialized:
            return None
        return opt_value.GetValueForExpressionPath('._object')

class UnionPrinter(SingleObjectContainerPrinter):
    def __init__(self, val: lldb.SBValue, _dict = None):
        super(UnionPrinter, self).__init__(val)
        if self.val is None:
            return
        self.size = self.val.GetType().GetNumberOfTemplateArguments()
        self.index = self.size

    def get_contained_value(self):
        self.index = self.val.GetValueForExpressionPath('._index').GetValueAsUnsigned()
        current_type = self.val.GetType().GetTemplateArgumentType(self.index)
        if self.index >= self.size:
            return None
        addr_of_object = self.val.GetValueForExpressionPath('._data._head').AddressOf()
        current_type_ptr = current_type.GetPointerType()
        addr_casted = addr_of_object.Cast(current_type_ptr)
        return addr_casted.Dereference()

    def summary_containing_value(self):
        return f'index {self.index}'

class TuplePrinter(ValuePrinter):
    def __init__(self, val: lldb.SBValue, _dict = None):
        super(TuplePrinter, self).__init__(val)
        if self.val is None:
            return
        self.size = self.val.GetType().GetNumberOfTemplateArguments()
        self.root_node = upcast_until(self.val, lambda value: strip_ns(strip_targs(value.GetType().GetName())) == 'TupleNode')

    def has_children(self):
        return self.size != 0

    def update(self):
        return self

    def num_children(self, _max_children):
        return self.size

    def get_child_index(self, name: str):
        if name[0] != '[' or name[-1] != ']':
            return -1
        return int(name[1:-1])

    def get_child_at_index(self, index):
        current = self.root_node
        for i in range(0, index):
            current = upcast(current, 0)
        return current.GetValueForExpressionPath('._nodeData').Clone(f'[{index}]')

    def to_string(self):
        if self.size == 0:
            return '[empty tuple]'
        return f'[tuple of {self.size} values]'

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
        (self.head, self.tail, self.element_size) = self.get_head_tail_element_size()
        return self

    def num_children(self, max_children = None):
        current = (self.tail.GetValueAsUnsigned() - self.head.GetValueAsUnsigned()) // self.element_size
        if max_children is None:
            return current
        return min(current, max_children)

    def has_children(self):
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
        return upcast_until(self.val, lambda val: strip_ns(strip_targs(val.GetType().GetName())) in
                                                  VectorPrinter.possible_base_classes)

    def __init__(self, val: lldb.SBValue, _dict = None):
        super(VectorPrinter, self).__init__(val)
        self.capacity = 0

    def get_head_tail_element_size(self) -> typing.Tuple[lldb.SBValue, lldb.SBValue, int]:
        as_base = self.as_base()
        head = as_base.GetValueForExpressionPath('._head')
        tail = as_base.GetValueForExpressionPath('._tail')
        element_size = as_base.EvaluateExpression('_head + 1').GetValueAsUnsigned() - \
                       as_base.EvaluateExpression('_head').GetValueAsUnsigned()
        return head, tail, element_size

    def update(self):
        super().update()
        self.capacity = self.as_base().GetValueForExpressionPath('._cap').GetValueAsUnsigned()
        return self

    def to_string(self):
        return f'[length {self.num_children()}, capacity {self.capacity}]'

class VectorViewPrinter(ContiguousRangePrinter):
    possible_base_classes = [
        'BaseDynamicVectorView',
        'BaseStaticVectorView'
    ]

    def as_base(self) -> lldb.SBValue:
        return upcast_until(self.val, lambda val: strip_ns(strip_targs(val.GetType().GetName())) in
                                                  VectorViewPrinter.possible_base_classes)

    def __init__(self, val: lldb.SBValue, _dict = None):
        super(VectorViewPrinter, self).__init__(val)

    def get_head_tail_element_size(self) -> typing.Tuple[lldb.SBValue, lldb.SBValue, int]:
        as_base = self.as_base()
        full_type_name = as_base.GetType().GetName()
        if strip_ns(strip_targs(full_type_name)) == 'BaseStaticVectorView':
            head = as_base.GetValueForExpressionPath('._addr')
            length = int(full_type_name.rsplit(',', 2)[-1].strip()[:-1].strip())
            tail = as_base.EvaluateExpression(f'_addr + {length}')
            element_size = as_base.EvaluateExpression('_addr + 1').GetValueAsUnsigned() - \
                           as_base.EvaluateExpression('_addr').GetValueAsUnsigned()
        else:
            head = as_base.GetValueForExpressionPath('._begin')
            tail = as_base.GetValueForExpressionPath('._end')
            element_size = as_base.EvaluateExpression('_begin + 1').GetValueAsUnsigned() - \
                           as_base.EvaluateExpression('_begin').GetValueAsUnsigned()
        return head, tail, element_size

    def to_string(self):
        return f'[length {self.num_children()}]'

    def update(self):
        super().update()
        return self

def string_summary(val, _dict):
    return StringPrinter(val).out()

def string_view_summary(val, _dict):
    return StringViewPrinter(val).out()

def optional_summary(val, _dict):
    return OptionalPrinter(val).update().out()

def union_summary(val, _dict):
    return UnionPrinter(val).update().out()

def tuple_summary(val, _dict):
    return TuplePrinter(val).update().out()

def vector_summary(val, _dict):
    return VectorPrinter(val).update().out()

def vector_view_summary(val, _dict):
    return VectorViewPrinter(val).update().out()

class NoChildProvider:
    def __init__(self, _1, _2):
        pass

    def has_children(self):
        return False

logging_enabled = True

def __lldb_init_module(debugger, _):
    global logging_enabled
    global logger
    global global_byte_order

    global_byte_order = debugger.GetSelectedTarget().GetByteOrder()

    if logging_enabled:
        lldb.formatters.Logger._lldb_formatters_debug_level = 2
        logger = lldb.formatters.Logger.Logger()

    def register_printer(ns: str, name: str, summarizer: str, child_provider: str):
        debugger.HandleCommand(
            f'type summary add -x \"^{ns}::{name}(<.*>)?([^:]*)?$\" -F cds_lldb.{summarizer} -p -r -w cds'
        ), debugger.HandleCommand(
            f'type synthetic add -x \"^{ns}::{name}(<.*>)?([^:]*)?$\" --python-class cds_lldb.{child_provider} -p -r -w cds'
        )

    register_printer('cds::impl', 'BaseString', 'string_summary', 'NoChildProvider')
    register_printer('cds::impl', 'BaseStringView', 'string_view_summary', 'NoChildProvider')

    register_printer('cds', 'Optional', 'optional_summary', 'OptionalPrinter')
    register_printer('cds::impl', 'Union', 'union_summary', 'UnionPrinter')
    register_printer('cds::impl', 'Tuple', 'tuple_summary', 'TuplePrinter')

    register_printer('cds::impl', 'Vector', 'vector_summary', 'VectorPrinter')
    register_printer('cds::impl', 'BaseVector', 'vector_summary', 'VectorPrinter')
    register_printer('cds::impl', 'VectorView', 'vector_view_summary', 'VectorViewPrinter')

    debugger.HandleCommand('type category enable cds')
