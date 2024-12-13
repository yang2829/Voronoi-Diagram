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

    def test_algo(self):
        g1 = _fortune.Fortune()
        g1.RunAlgo()
        points = g1.get_points()
        edges = g1.get_edges()
