import typing

class SBFrame:
    ...

class SBValue:
    def __init__(self):
        self.changed: bool = False
        self.addr: addr_t = addr_t()
        self.address_of: addr_t = addr_t()

    def CreateChildAtOffset(self, name: str, offset: int, type: 'SBType') -> 'SBValue':
        ...

    def GetChildMemberWithName(self, name: str) -> 'SBValue':
        ...

    def GetFrame(self) -> 'SBFrame':
        ...

    def CreateValueFromData(self, name: str, data: 'SBData', t: 'SBType') -> 'SBValue':
        ...

    def AddressOf(self) -> 'SBValue':
        ...

    def Clone(self, new_name: str) -> 'SBValue':
        ...

    def GetName(self) -> str:
        ...

    def Dereference(self) -> 'SBValue':
        ...

    def GetNonSyntheticValue(self) -> 'SBValue':
        ...

    def GetLocation(self) -> str:
        ...

    def IsSynthetic(self) -> bool:
        ...

    def IsDynamic(self) -> bool:
        ...

    def GetSyntheticValue(self) -> 'SBValue':
        ...

    def EvaluateExpression(self, expr: str, options: 'SBExpressionOptions' = None) -> 'SBValue':
        ...

    def GetValueAsAddress(self) -> 'addr_t':
        ...

    def GetValueAsUnsigned(self) -> int:
        ...

    def GetValueAsSigned(self) -> int:
        ...

    def GetPointeeData(self, offset: int = 0, length: int = 1) -> 'SBData':
        ...

    def IsValid(self) -> bool:
        ...

    def GetValueForExpressionPath(self, path: str) -> 'SBValue':
        ...

    def GetChildAtIndex(self, index) -> 'SBValue':
        ...

    def GetType(self) -> 'SBType':
        ...

    def GetData(self) -> 'SBData':
        ...

    def Cast(self, t: 'SBType') -> 'SBValue':
        ...

class addr_t:
    ...

class offset_t:
    ...

class SBError:
    ...

class ByteOrder:
    ...

class SBData:
    def __init__(self):
        self.address: addr_t = addr_t()
        self.uint8: typing.List[int] = []
        self.double: typing.List[float] = []

    def GetByteOrder(self) -> ByteOrder:
        ...

    @classmethod
    def CreateDataFromUInt64Array(cls, endian: ByteOrder, addr_byte_size: int, array: typing.List[int]) -> 'SBData':
        ...

    def GetDouble(self, error: 'SBError', offset: offset_t) -> float:
        ...

class SBType:
    def __init__(self):
        self.name: str = ''
        self.template_args: typing.List['SBType'] = []

    def GetByteAlign(self) -> int:
        ...

    def GetByteSize(self) -> int:
        ...

    def GetName(self) -> str:
        ...

    def GetPointeeType(self) -> 'SBType':
        ...

    def GetNumberOfTemplateArguments(self) -> int:
        ...

    def GetTemplateArgumentType(self, index: int) -> 'SBType':
        ...

    def IsPointerType(self) -> bool:
        ...

    def GetUnqualifiedType(self) -> 'SBType':
        ...

    def IsReferenceType(self) -> bool:
        ...

    def GetDereferencedType(self) -> 'SBType':
        ...

    def GetDirectBaseClassAtIndex(self, idx: int) -> 'SBTypeMember':
        ...

    def GetNumberOfDirectBaseClasses(self) -> int:
        ...

    def IsValid(self) -> bool:
        ...

    def GetPointerType(self) -> 'SBType':
        ...

class SBTypeMember:
    def GetType(self) -> 'SBType':
        ...

class formatters:
    class Logger:
        _lldb_formatters_debug_level = 0
        class Logger:
            def __init__(self):
                pass

            def write(self, val: str):
                ...

class SBExpressionOptions:
    def __init__(self):
        pass
