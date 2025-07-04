import typing

class SBValue:
    def __init__(self):
        self.addr: addr_t = addr_t()
        self.address_of: addr_t = addr_t()

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

    def EvaluateExpression(self, expr: str) -> 'SBValue':
        ...

    def GetValueAsAddress(self) -> 'addr_t':
        ...

    def GetValueAsUnsigned(self) -> int:
        ...

    def GetPointeeData(self, offset: int, length: int) -> 'SBData':
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

class SBData:
    def __init__(self):
        self.address: addr_t = addr_t()
        self.uint8: typing.List[int] = []

class SBType:
    def __init__(self):
        self.name: str = ''

    def IsPointerType(self) -> bool:
        ...

    def IsReferenceType(self) -> bool:
        ...

    def GetDirectBaseClassAtIndex(self, idx: int) -> 'SBTypeMember':
        ...

    def GetNumberOfDirectBaseClasses(self) -> int:
        ...

    def IsValid(self) -> bool:
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
