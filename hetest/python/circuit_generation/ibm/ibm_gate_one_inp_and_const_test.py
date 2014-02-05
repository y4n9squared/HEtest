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
#  Description:        IBM TA2 one input and constant gate superclass test 
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  8 Nov 2012    SY             Original Version
# *****************************************************************

import ibm_wire as iw
import ibm_gate_one_inp_and_const as igoiac
import ibm_circuit as ic
import unittest

class TestGateOneInpAndConst(unittest.TestCase):

    def test_get_inputs(self):
        """
        Tests that the get_inputs method functions as expected.
        """
        L = 20
        circuit = ic.IBMCircuit(L)
        gate_name = "g"
        D = 10
        input1 = iw.IBMInputWire("w1", circuit)
        const = "constant"
        g = igoiac.IBMGateOneInpAndConst(gate_name, D, input1, const, circuit)
        self.assertEqual([input1], g.get_inputs())

if __name__ == '__main__':
    stc.unittest.main()

