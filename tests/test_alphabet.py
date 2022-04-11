import pickle
import unittest

from subseq.alphabet import Alphabet


class AlphabetTest(unittest.TestCase):
    def setUp(self):
        self.alphabet = Alphabet()
        for symbol in "SUBSEQ":
            self.alphabet.add_symbol(symbol)

    def test_setup(self):
        self.assertEqual(self.alphabet.length(), 6)
        self.assertEqual(
            self.alphabet.indexes, {"$": 0, "S": 1, "U": 2, "B": 3, "E": 4, "Q": 5}
        )
        self.assertEqual(self.alphabet.symbols, ["$", "S", "U", "B", "E", "Q"])

    def test_get_known_symbol(self):
        self.assertEqual(self.alphabet.get_symbol(1), "S")

    def test_get_unknown_symbol(self):
        self.assertIsNone(self.alphabet.get_symbol(42))

    def test_get_known_index(self):
        self.assertEqual(self.alphabet.get_index("U"), 2)

    def test_get_unknown_index(self):
        self.assertEqual(self.alphabet.get_index("X"), -1)

    def test_add_known_symbol(self):
        self.assertEqual(self.alphabet.add_symbol("U"), 2)
        self.assertEqual(self.alphabet.length(), 6)

    def test_add_unknown_symbol(self):
        self.assertEqual(self.alphabet.add_symbol("X"), 6)
        self.assertEqual(self.alphabet.length(), 7)

    def test_pickle(self):
        pickled = pickle.dumps(self.alphabet)
        unpickled_alphabet = pickle.loads(pickled)
        self.assertEqual(self.alphabet, unpickled_alphabet)
