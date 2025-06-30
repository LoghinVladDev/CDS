from tools.gdb_pretty_printers import cds_pretty_printer as pp
import unittest

def write(str):
    print(str)

pretty_printers = []

pp.write = write

class Type:
    def __init__(self):
        self.code = 0
        self.name = 'cds::Optional<int>'

    def strip_typedefs(self):
        return self

class Value:
    def __init__(self, t_type: Type, values: dict = {}):
        self.type = t_type
        self.values = values

    def __getitem__(self, item):
        return self.values[item]


class TestOptionalPrinter(unittest.TestCase):
    def test_print(self):
        res = pp.printer_registry(Value(
            Type(),
            {
                "_exists": True,
                "_object": 5
            }
        ))

        self.assertIs(res.to_string(), '')

if __name__ == '__main__':
    pp.register_pretty_printers()
    unittest.main()
