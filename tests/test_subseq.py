import pickle
import unittest

from subseq.subseq import Subseq


class SubseqTest(unittest.TestCase):
    def test_predict(self):
        model = Subseq(0)
        model.fit(["banana"])
        self.assertEqual(model.predict("ana"), "n")

    def test_predict_with_unknown_symbol(self):
        model = Subseq(0)
        model.fit(["banana"])
        self.assertEqual(model.predict("wna"), "n")

    def test_predict_k(self):
        model = Subseq(0)
        model.fit(["ab", "ac", "ac"])
        self.assertEqual(model.predict_k("a", 2), ["c", "b"])

    def test_pickle(self):
        model = Subseq(0)
        model.fit(["banana"])
        pickled = pickle.dumps(model)
        unpickled_model = pickle.loads(pickled)
        self.assertEqual(model, unpickled_model)
