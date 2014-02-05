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
#  Description:        IBM TA2 wire class test 
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  17 Oct 2012   SY             Original Version
# *****************************************************************

import ibm_circuit as ic
import ibm_wire as iw
import unittest

class TestWire(unittest.TestCase):

    def setUp(self):
        pass

    def test_get_depth(self):
        """
        Test that getting depth returns 0.0.
        """
        L = 15
        circuit = ic.IBMCircuit(L)
        w1_name = "w1"
        w1 = iw.IBMInputWire(w1_name, circuit)
        self.assertEquals(0, w1.get_depth())

    def test_get_level(self):
        """
        Test that getting level returns 0.
        """
        L = 15
        circuit = ic.IBMCircuit(L)
        w1_name = "w1"
        w1 = iw.IBMInputWire(w1_name, circuit)
        self.assertEquals(0, w1.get_level())

if __name__ == '__main__':
    stc.unittest.main()

