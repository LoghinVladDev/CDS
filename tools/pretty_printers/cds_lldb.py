# Installation:
#   - Via init file
#   - echo 'command script import "/path/to/cds/lldb/pretty/printer/cds_lldb.py"'

import typing
from abc import abstractmethod, ABC

try:
    import lldb
except:
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
            self.summary = ''
            self.val = None
            return

        if self.val.GetType().IsPointerType():
            self.val = self.val.Dereference()

    @abstractmethod
    def to_string(self):
        ...

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

def string_summary(val, _dict):
    return StringPrinter(val).to_string()

def string_view_summary(val, _dict):
    return StringViewPrinter(val).to_string()

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

    debugger.HandleCommand('type category enable cds')
