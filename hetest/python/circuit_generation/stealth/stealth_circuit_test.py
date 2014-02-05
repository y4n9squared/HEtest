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
#  Description:        Stealth TA2 circuit class test 
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  08 Nov 2012   SY             Original Version
# *****************************************************************

import stealth_wire as sw
import stealth_gate_and as sga
import stealth_gate_or as sgo
import stealth_gate_xor as sgx
import stealth_circuit as sc
import unittest
import common.spar_random as sr

class TestAndGate(unittest.TestCase):

    def setUp(self):
        # create a simple sample circuit:
        w1 = sw.StealthInputWire("w1", True)
        w2 = sw.StealthInputWire("w2", True)
        w3 = sw.StealthInputWire("w3", False)
        g1 = sga.StealthAndGate("g1", [w1, w2], [True, False])
        g2 = sgo.StealthOrGate("g2", [g1, w3], [False, False])
        output_gate = sgx.StealthXorGate("og", [g1, g2],
                                         [False, False])
        self.circ = sc.StealthCircuit([w1, w2, w3], output_gate)


    def test_simple_circuit_example(self):
        """
        Tests that in the simple circuit example given above, the methods
        get_num_inputs, display, and evaluate work as intended.
        """
        self.assertEqual("\nL\ng1:AND(N(w1),w2)\nL\ng2:OR(g1,w3)\nL\nog:XOR(g1,g2)",
                         self.circ.display())
        self.assertEqual(3, self.circ.get_num_inputs())
        self.assertEqual(False, self.circ.evaluate([True, True, False]))
        self.assertEqual(True, self.circ.evaluate([True, True, True]))

    # TODO: need more tests here
        
if __name__ == '__main__':
    stc.unittest.main()
