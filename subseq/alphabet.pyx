from cpython.object cimport Py_EQ, Py_NE


cdef class Alphabet:
    def __cinit__(self, unknown_symbol="$"):
        self.indexes = {}
        self.symbols = []
        self.add_symbol(unknown_symbol)

    def length(self):
        return len(self.symbols)

    def get_symbol(self, int index):
        if 0 <= index < self.length():
            return self.symbols[index]
        return None

    def get_index(self, symbol):
        return self.indexes.get(symbol, NOT_AN_INDEX)

    def add_symbol(self, symbol):
        cdef int index = self.indexes.setdefault(symbol, self.length())
        if index == self.length():
            self.symbols.append(symbol)
        return index

    def __getstate__(self):
        return (self.indexes, self.symbols)

    def __setstate__(self, state):
        indexes, symbols = state
        self.indexes = indexes
        self.symbols = symbols

    def __is_equal__(self, other):
        return self.indexes == other.indexes and \
               self.symbols == other.symbols

    def __richcmp__(self, other, op):
        if op == Py_EQ:
            return self.__is_equal__(other)
        elif op == Py_NE:
            return not self.__is_equal__(other)
        else:
            assert False

    def __repr__(self):
        return f"{{indexes: {self.indexes}, symbols: {self.symbols}}}"
