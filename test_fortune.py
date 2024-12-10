import sys
import os
import timeit
import unittest

# The python module that wraps the matrix code.
import _matrix

class PyApiTest(unittest.TestCase):

    def test_construct(self, size):

        g1 = _fortune.Fortune(8)
        self.assertEqual(8, g1.npoints())
        self.assertEqual(500, g1.getw())
        self.assertEqual(500, g1.geth())