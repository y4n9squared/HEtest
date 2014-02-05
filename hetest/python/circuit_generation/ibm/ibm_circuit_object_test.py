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
#  Description:        IBM TA2 circuit object superclass test
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  22 Oct 2012   SY             Original version
# *****************************************************************

import ibm_circuit_object as ico
import ibm_circuit as ic
import unittest

class CircuitObjectTest(unittest.TestCase):

    def test_bad_displayname_init(self):
        """
        Tests that initializing a circuit object with an empty string
        as a displayname throws an error.
        """
        D = 5
        level = 2
        batch_size = 10
        circuit = ic.IBMCircuit(batch_size)
        self.assertRaises(AssertionError,
                          ico.IBMCircuitObject, "", D, level, circuit)
                
    def test_get_name(self):
        """
        Tests to see that the get_name method functions as expected.
        """
        co1_name = "object1"
        D = 5
        level = 2
        batch_size = 10
        circuit = ic.IBMCircuit(batch_size)
        co1 = ico.IBMCircuitObject(co1_name, D, level, circuit)
        self.assertEqual(co1_name, co1.get_name())
        
    def test_get_depth(self):
        """
        Tests to see that the get_depth method functions as expected.
        """
        co1_name = "object1"
        D = 5
        level = 2
        batch_size = 10
        circuit = ic.IBMCircuit(batch_size)
        co1 = ico.IBMCircuitObject(co1_name, D, level, circuit)
        self.assertEqual(D, co1.get_depth())

    def test_get_level(self):
        """
        Tests to see that the get_level method functions as expected.
        """
        co1_name = "object1"
        D = 5
        level = 2
        batch_size = 10
        circuit = ic.IBMCircuit(batch_size)
        co1 = ico.IBMCircuitObject(co1_name, D, level, circuit)
        self.assertEqual(level, co1.get_level())

    def test_get_batch_size(self):
        """
        Tests to see that the get_batch_size method functions as expected.
        """
        co1_name = "object1"
        D = 5
        level = 2
        batch_size = 10
        circuit = ic.IBMCircuit(batch_size)
        co1 = ico.IBMCircuitObject(co1_name, D, level, circuit)
        self.assertEqual(batch_size, co1.get_batch_size())

if __name__ == '__main__':
    stc.unittest.main()
