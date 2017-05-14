#!/usr/local/bin/python3

import m1
import unittest

class TestLinearRegression(unittest.TestCase):

    def test_cost(self):
        xs = [1,3,9,12,15]
        ys = [44,30,20,15,11]
        theta0 = 4.0
        theta1 = 5.0
        self.assertEqual(m1.cost_function(xs, ys, theta0, theta1), 921.2)

if __name__ == '__main__':
    unittest.main()

