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
#  Description:        Stealth TA2 gate superclass test
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  19 Oct 2012   SY             Original Version
#  08 Nov 2012   SY             Incorporated Oliver's feedback
# *****************************************************************

import stealth_gate as sg
import stealth_wire as sw
import unittest

class GateTest(unittest.TestCase):

    def setUp(self):
        pass

    def test_bad_init(self):
        """
        Tests that bad gate initializations, such as initializations with
        lists of inputs and lists of negations of unequal length, throw an
        error.
        """
        # note that the inputs list should typically only contain circuit
        # objects. However, for these tests, we make an exception, since we
        # do not actually make use of the properties of these elements.
        inputs = ["input1","input2","input3"]
        negations = [True, True, False, False]
        displayname = "gate"
        self.assertRaises(AssertionError,
                          sg.StealthGate, displayname, inputs, negations)

    def test_unimplemented_methods(self):
        """
        Tests that calling methods which are only implemented in subclasses,
        of calling methods which rely on other methods only implemented in
        subclasses, causes AssertionErrors.
        """
        #Initialize the input wires:
        wire1 = sw.StealthInputWire("wire1", True)
        wire2 = sw.StealthInputWire("wire2", False)
        #Initialize the gate:
        gate = sg.StealthGate("gate", [wire1, wire2], [False, False])

        self.assertRaises(AssertionError,
                          gate.get_full_display_string)

        self.assertRaises(AssertionError,
                          gate.evaluate)
        
        self.assertRaises(AssertionError,
                          gate.balance, True)
        
if __name__ == '__main__':
    stc.unittest.main()
