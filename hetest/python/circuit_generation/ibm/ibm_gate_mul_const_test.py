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
#  Description:        Stealth TA2 multiplication by constant gate calss test 
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  17 Oct 2012   SY             Original Version
# *****************************************************************

import ibm_batch as ib
import ibm_wire as iw
import ibm_gate_mul_const as igmc
import ibm_circuit as ic
import unittest
import circuit_generation.circuit_common.circuit_input as ci

class TestMulConstGate(unittest.TestCase):

    def test_get_full_display_string(self):
        """
        Tests that the method get_full_display_string returns the correct
        string.
        """
        #Initialize the circuit:
        circuit = ic.IBMCircuit(10)
        #Initialize the input wire:
        w1 = iw.IBMInputWire("w1", circuit)
        #Initialize the constnat:
        const = ci.Input([ib.IBMBatch([True, False])])
        #Initialize the gate:
        g = igmc.IBMMulConstGate("g", w1, const, circuit)
        self.assertEquals("g:LMULconst(w1,[10])", g.get_full_display_string())

    def test_get_depth(self):
        """
        Tests that the get_depth method returns the correct depth, as defined
        by IBM.
        """
        circuit = ic.IBMCircuit(10)
        w1 = iw.IBMInputWire("w1", circuit)
        const = ib.IBMBatch([True, False])
        g1 = igmc.IBMMulConstGate("g1", w1, const, circuit)
        g2 = igmc.IBMMulConstGate("g2", g1, const, circuit)
        g3 = igmc.IBMMulConstGate("g3", g2, const, circuit)
        self.assertEqual(.5, g1.get_depth())
        self.assertEqual(1, g2.get_depth())
        self.assertEqual(1.5, g3.get_depth())
    
if __name__ == '__main__':
    stc.unittest.main()

