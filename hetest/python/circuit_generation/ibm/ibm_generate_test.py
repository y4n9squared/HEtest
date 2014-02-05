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
#  Description:        IBM TA2 circuit generation test
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  12 Nov 2012   SY             Original Version
# *****************************************************************

import time
import os
import StringIO
import ibm_generate as gen
import unittest
import common.spar_random as sr
import circuit_generation.circuit_common.test_file_handle_object as tfho

class generate_test(unittest.TestCase):

    def setUp(self):
        """
        Records the randomness used.
        """
        # record the randomness used in case the test fails:
        rand_seed = int(time.time())
        sr.seed(rand_seed)
        print("seed for this test: " + str(rand_seed))        

    def test_simple_config_file(self):
        """
        tests that the key, input, circuit and test files are roughly as
        expected in a simple case.
        """
        # create the config file:
        test_name = "unit_test_test_1"
        K = "'key'"
        L =  10
        D = 3.0
        W = 5
        num_circuits = 1
        num_inputs = 1
        config_file_text = "\n".join(["test_type = RANDOM",
                                      " = ".join(["K", str(K)]),
                                      " = ".join(["L", str(L)]),
                                      " = ".join(["D", str(D)]),
                                      " = ".join(["W", str(W)]),
                                      " = ".join(["num_circuits",
                                                  str(num_circuits)]),
                                      " = ".join(["num_inputs",
                                                  str(num_inputs)]),
                                      " = ".join(["generate", "True"])])
        config_file = StringIO.StringIO(config_file_text)
        # create the parser/generator:
        fho = tfho.test_file_handle_object()
        pag = gen.parser_and_generator(test_name, config_file, fho)
        pag.parse_and_generate()
        # retrieve the test file and check that it is correct:
        test_file = fho.get_file(os.path.join(test_name, "test.txt"))
        test_file_text = test_file.getvalue()
        expected_test_file_text = "\n".join(
            ["KEY",
             os.path.join("ibm", test_name, "key", str(1)),
             "CIRCUIT",
             os.path.join("ibm", test_name, "circuit", str(1)),
             "INPUT",
             os.path.join("ibm", test_name, "input", str(1)),
             ""])
        self.assertEqual(expected_test_file_text, test_file_text)
        # retrieve the key file and check that it is correct:
        key_file = fho.get_file(os.path.join(test_name, "key", "1"))
        key_file_text = key_file.getvalue()
        expected_key_file_text = ",".join(["=".join(["L", str(L)]),
                                           "=".join(["D", str(D)]),
                                           "=".join(["K", str(K)])])
        self.assertEqual(expected_key_file_text, key_file_text)
        # retrieve the input and check that it is correct:
        input_file = fho.get_file(os.path.join(test_name, "input", "1"))
        input_file_text = input_file.getvalue()
        # check that input text begins and ends with a bracket:
        self.assertEqual("[", input_file_text[0])
        self.assertEqual("]", input_file_text[-1])
        input_batches = input_file_text[1:-1].split(",")
        # check that the number of batches is correct:
        self.assertEqual(W, len(input_batches))
        # check that all batch characters are bits:
        for batch in input_batches:
            for bit in batch:
                self.assertTrue((bit == '0') or (bit == '1'))
        # retrieve the circuit and check that it begins with the correct header:
        circuit_file = fho.get_file(os.path.join(test_name, "circuit", "1"))
        circuit_file_text = circuit_file.getvalue()
        circuit_header = circuit_file_text.split("\n")[0]
        (W_string, D_string, L_string) = circuit_header.split(",")
        W_value = int(W_string.split("=")[-1])
        D_value = float(D_string.split("=")[-1])
        L_value = int(L_string.split("=")[-1])
        self.assertEqual(W, W_value)
        self.assertTrue((D <= D_value) and (D + 1.0 > D_value))
        self.assertEqual(L, L_value)
        
if __name__ == '__main__':
    stc.unittest.main()
