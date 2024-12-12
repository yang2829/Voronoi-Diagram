import _fortune
import pytest
import unittest

class PyApiTest(unittest.TestCase):

    def test_init(self):

        g1 = _fortune.Fortune(8)
        self.assertEqual(8, g1.npoints())
        self.assertEqual(500, g1.getw())
        self.assertEqual(500, g1.geth())