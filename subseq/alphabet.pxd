cdef enum:
    NOT_AN_INDEX = -1

ctypedef size_t Symbol

cdef class Alphabet:
    cdef public:
        dict indexes
        list symbols
