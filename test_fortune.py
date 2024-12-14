import _fortune
import pytest
import unittest

class PyApiTest(unittest.TestCase):

    def test_init(self):
        g1 = _fortune.Fortune(6)
        self.assertEqual(6, g1.npoints())
        self.assertEqual(500, g1.getw())
        self.assertEqual(500, g1.geth())
        g1 = _fortune.Fortune(10, 300, 400)
        self.assertEqual(10, g1.npoints())
        self.assertEqual(300, g1.getw())
        self.assertEqual(400, g1.geth())

    def test_random(self):
        g1 = _fortune.Fortune()
        g1.RunAlgo()
        edges = g1.get_edges()
        for e in edges:
            tmpx = e.s[0] - e.d[0]
            tmpy = e.s[1] - e.d[1]
            if (abs(tmpx) < 1e-2):
                assert abs(e.v[0]) < 1e-2
            else:
                assert abs(abs(tmpy/tmpx) - abs(e.v[1]/e.v[0])) < 1e-5
