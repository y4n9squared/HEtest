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
#  Description:        IBM TA2 gate superclass test 
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  8 Nov 2012    SY             Original Version
# *****************************************************************

import ibm_circuit as ic
import ibm_wire as iw
import ibm_gate as ig
import unittest

class TestGate(unittest.TestCase):

    def test_unimplemented_methods(self):
        """
        Tests that calling methods which are only implemented in subclasses
        causes errors.
        """
        L = 10
        circuit = ic.IBMCircuit(L)
        w1 = iw.IBMInputWire("w1", circuit)
        w2 = iw.IBMInputWire("w2", circuit)
        D = 10
        level = 9
        g = ig.IBMGate("g", D, level, circuit)
        # AssertionError expected:
        self.assertRaises(AssertionError,
                          g.get_func_name)

if __name__ == '__main__':
    stc.unittest.main()

