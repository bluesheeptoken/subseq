import unittest

from subseq.subseq import Subseq
import pickle


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

    def test_predict_k_not_enough_predictions(self):
        model = Subseq(0)
        model.fit(["ab", "ac", "ac"])
        self.assertEqual(model.predict_k("a", 3), ["c", "b"])

    def test_predict_k_with_weights(self):
        model = Subseq(0)
        model.fit(["ab", "ac", "ac"])
        self.assertEqual(model.predict_k_with_weights("a", 2), {"c": 8.0, "b": 4.0})

    def test_predict_k_with_weights_not_enough_predictions(self):
        model = Subseq(0)
        model.fit(["ab", "ac", "ac"])
        self.assertEqual(model.predict_k_with_weights("a", 3), {"c": 8.0, "b": 4.0})

    def test_pickle(self):
        model = Subseq(0)
        model.fit(["banana"])
        pickled = pickle.dumps(model)
        unpickled = pickle.loads(pickled)
        self.assertEqual(unpickled.predict("ana"), "n")
