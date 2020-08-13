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
