# distutils: language = c++

from libcpp.vector cimport vector
from subseq.alphabet cimport Alphabet
from libcpp.string cimport string


cdef extern from "cpp_sources/CSubseq.hpp":
    cdef cppclass CSubseq nogil:
        CSubseq(vector[int], int, int) except +
        CSubseq(string) except +
        int predict(vector[int])
        vector[int] predict_k(vector[int], int)
        string get_state()

cdef class Subseq:
    cdef CSubseq *thisptr
    cdef readonly Alphabet alphabet
    cdef public int threshold_query

    def __init__(self, int threshold_query=0):
        self.alphabet = Alphabet()
        self.threshold_query = threshold_query

    def fit(self, sequences):
        cdef vector[int] text
        for sequence in sequences:
            for symbol in sequence:
                text.push_back(self.alphabet.add_symbol(symbol))
            text.push_back(0)  # Separate sequences by symbol 0

        self.thisptr = new CSubseq(text, self.alphabet.length(), self.threshold_query)

    def __dealloc__(self):
        del self.thisptr

    def predict(self, query):
        cdef vector[int] int_query
        for symbol in query:
            int_query.push_back(self.alphabet.get_index(symbol))
        return self.alphabet.get_symbol(self.thisptr.predict(int_query))

    def predict_k(self, query, k):
        cdef vector[int] int_query
        cdef vector[int] predictions
        for symbol in query:
           int_query.push_back(self.alphabet.get_index(symbol))
        predictions = self.thisptr.predict_k(int_query, k)
        return [self.alphabet.get_symbol(index) for index in predictions]

    def __getstate__(self):
        return (self.thisptr.get_state(),
                self.alphabet,
                self.threshold_query)


    def __setstate__(self, state):
        subseq_state, alphabet, threshold_query = state
        self.thisptr = new CSubseq(subseq_state)
        self.alphabet = alphabet
        self.threshold_query = threshold_query
