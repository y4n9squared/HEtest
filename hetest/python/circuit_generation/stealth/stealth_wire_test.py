# *****************************************************************
# Copyright (c) 2013 Massachusetts Institute of Technology
#
# Developed exclusively at US Government expense under US Air Force contract
# FA8721-05-C-002. The rights of the United States Government to use, modify,
# reproduce, release, perform, display or disclose this computer software and
# computer software documentation in whole or in part, in any manner and for
# any purpose whatsoever, and to have or authorize others to do so, are
# Unrestricted and Unlimited.
#
# Licensed for use under the BSD License as described in the BSD-LICENSE.txt
# file in the root directory of this release.
#  
#  Project:            SPAR
#  Authors:            SY
#  Description:        Stealth TA2 wire class test 
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  17 Oct 2012   SY             Original Version
# *****************************************************************

import stealth_wire as sw
import unittest

class TestWire(unittest.TestCase):

    def setUp(self):
        pass

    def test_good_input(self):
        """
        Test wire setting and evaluation when the input is valid (a boolean).
        """
        w1_name = "w1"
        w1 = sw.StealthInputWire(w1_name, True)
        # a wire with a 'True' input should evaluate to 'True'.
        w1.set_input(True)
        self.assertEqual(w1.evaluate(), True)
        # a wire with a '1' input should evaluate to 'True'.
        w1.set_input(1)
        self.assertEqual(w1.evaluate(), True)
        # a wire with a 'False' input should evaluate to 'False'.
        w1.set_input(False)
        self.assertEqual(w1.evaluate(), False)
        # a wire with a '0' input should evaluate to 'False'.
        w1.set_input(0)
        self.assertEqual(w1.evaluate(), False)

    def test_bad_input(self):
        """
        Test wire input setting when the input is not valid
        (not a boolean or something that evaluates as such).
        An error should be thrown.
        """
        # setting a non-boolean input should throw an AssertionError.
        w1_name = "w1"
        w1 = sw.StealthInputWire(w1_name, None)
        self.assertRaises(AssertionError, w1.evaluate)
        w1 = sw.StealthInputWire(w1_name, "this_is_a_string")
        self.assertRaises(AssertionError, w1.evaluate)

if __name__ == '__main__':
    stc.unittest.main()

