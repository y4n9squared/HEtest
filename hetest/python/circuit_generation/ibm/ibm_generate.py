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
#  Description:        The IBM circuit generation main method 
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  08 May 2012   SY             Original Version
# *****************************************************************

from optparse import OptionParser
import os
import sys
this_dir = os.path.dirname(os.path.abspath(__file__))
base_dir = os.path.join(this_dir, '../..')
sys.path.append(base_dir)

import ibm_generation_functions as igf
import circuit_generation.circuit_common.file_handle_object as fho

class parser_and_generator(object):
    """
    This class parses the config file living in the directory test_name,
    and generates corresponding circuits.
    A config.txt should contain text of the following format:
    K = 80
    L = 100
    D = 10
    W = 200
    num_circuits = 2
    num_inputs = 5
    this means that 2 circuits should  be created with the parameters L = 100,
    D = 10 and W = 200, and that 5 inputs should be generated for each such
    circuit.
    all 8 possible parameters (test_type, K, L, D, num_levels, W, num_circuits,
    and num_inputs) can be reset multiple times throughout the config.txt file.
    For the large and varying parameters tests, test_type should be 'random' and
    K, L, D, W, num_circuits and num_inputs should be specified.
    For the single gate type test, test_type should change throughout the test;
    it should take on the values 'add', 'addconst', 'mul', 'mulconst', 'select',
    and 'rotate'. K, L, num_levels, W, num_circuits and num_inputs should be
    specified.
    Each time num_inputs is specified, generation will occur with the current
    values. Generation stores numbered circuits in the 'circuit' directory in
    the 'test_name' folder, numbered inputs in the 'input' directory, and
    numbered security parameters in the 'key' directory.
    It also generates a 'test.txt' file which lists the paths to the keys,
    circuits and inputs in the order in which they are used.
    """
    def __init__(self, test_name, config_file, file_handle_object):
        """
        Initializes the class with a config_file, a test_name and a
        file_handle_object.
        Test_name should correspond to a directory with the name 'test_name'.
        """
        self.__config_file_lines = config_file.read().split("\n")
        self.__test_name = test_name
        self.__fho = file_handle_object
        # initialize the key, circuit and input directory names:
        self.__key_dir_name = os.path.join(self.__test_name, "key")
        self.__circuit_dir_name = os.path.join(self.__test_name, "circuit")
        self.__input_dir_name = os.path.join(self.__test_name, "input")
        # make the key, circuit and input folders:
        self.__fho.create_dir(self.__key_dir_name)
        self.__fho.create_dir(self.__circuit_dir_name)
        self.__fho.create_dir(self.__input_dir_name)
        # initialize the key, circuit and input counters to 0:
        self.__unique_key_num = 0
        self.__unique_circuit_num = 0
        self.__unique_input_num = 0
        # create the map which maps line to line handler:
        self.__line_to_handler = {"test_type": self.__handle_test_type,
                                  "K": self.__handle_k,
                                  "L": self.__handle_l,
                                  "D": self.__handle_d,
                                  "W": self.__handle_w,
                                  "num_levels": self.__handle_num_levels,
                                  "num_circuits": self.__handle_num_circuits,
                                  "num_inputs": self.__handle_num_inputs,
                                  "generate": self.__handle_generate}
        # stores the latest key recorded, in order to detect changes:
        self.__latest_key = None

    def __handle_test_type(self, test_type):
        """Handles a new test type appropriately."""
        self.__test_type = igf.TEST_TYPES.value_to_number[test_type]
        
    def __handle_k(self, K):
        """Handles a new security parameter appropriately."""
        self.__K = K
        
    def __handle_l(self, L):
        """Handles a new batch size appropriately."""
        self.__L = int(L)

    def __handle_d(self, D):
        """Handles a new depth appropriately."""
        self.__D = float(D)

    def __handle_w(self, W):
        """Handles a new width appropriately."""
        self.__W = int(W)

    def __handle_num_levels(self, num_levels):
        """Handles a new num_levels appropriately."""
        self.__num_levels = int(num_levels)

    def __handle_num_circuits(self, num_circuits):
        """Handles a new number of circuits appropriately."""
        self.__num_circuits = int(num_circuits)

    def __handle_num_inputs(self, num_inputs):
        """Handles a new number of inputs appropriately."""
        self.__num_inputs = int(num_inputs)

    def __handle_generate(self, generate):
        """Handles a 'generate = True' command"""
        if eval(generate):
            self.__make_circuits()

    def __handle_new_key(self):
        """Writes the new key (consisting of K, L, D (or num_levels))."""
        if self.__test_type == igf.TEST_TYPES.RANDOM:
            sec_param_text = ",".join(["L" + "=" + str(self.__L),
                                       "D" + "=" + str(self.__D),
                                       "K" + "=" + str(self.__K)])
        else:
            sec_param_text = ",".join(["L" + "=" + str(self.__L),
                                       "D" + "=" +
                                       str(self.__num_levels),
                                       "K" + "=" + str(self.__K)])
        # Only update the key if there have been changes to it:
        if sec_param_text != self.__latest_key:
            self.__latest_key = sec_param_text
            self.__unique_key_num += 1
            # write the security parameter to a key file:
            sec_param_file_name = os.path.join(self.__key_dir_name,
                                               str(self.__unique_key_num))
            sec_param_file = self.__fho.get_file_object(sec_param_file_name, 'w')
            sec_param_file.write(sec_param_text)
            self.__fho.close_file_object(sec_param_file)
            # write the key location to the test file:
            self.__test_file.write(
                "".join(["KEY\n", os.path.join("ibm", sec_param_file_name),
                         "\n"]))
        
    def __make_circuits(self):
        """Generates circuits with the current parameters"""
        # update the key if needed:
        self.__handle_new_key()
        # make self.__num_circuits circuits:
        for circuit_num in xrange(self.__num_circuits):
            # generate a random circuit:
            if self.__test_type == igf.TEST_TYPES.RANDOM:
                gen = igf.TEST_TYPE_TO_GENERATOR_BY_DEPTH[igf.TEST_TYPES.RANDOM]
                circ = gen(self.__L, self.__D, self.__W)
            else:
                gen = igf.TEST_TYPE_TO_GENERATOR_BY_LEVEL[self.__test_type]
                circ = gen(self.__L, self.__num_levels, self.__W)
            self.__write_circuit(circ)
            # for each circuit, make self.__num_inputs inputs:
            for input_num in xrange(self.__num_inputs):
                # generate a random input:
                inp = igf.make_random_input(self.__L, self.__W)
                self.__write_input(inp)

    def __write_circuit(self, circ):
        """Handles writing a circuit, both to the circuit file and to the test
        file."""
        self.__unique_circuit_num += 1
        # write the circuit to the circuit file:
        circuit_file_name = os.path.join(self.__circuit_dir_name,
                                         str(self.__unique_circuit_num))
        circuit_file = self.__fho.get_file_object(circuit_file_name, 'w')
        circuit_file.write(circ.display())
        self.__fho.close_file_object(circuit_file)
        # write the circuit location to the test file:
        self.__test_file.write(
            "".join(["CIRCUIT\n", os.path.join("ibm", circuit_file_name),
                     "\n"]))

    def __write_input(self, inp):
        """Handles writing an input, both to the input file and to the test
        file."""
        self.__unique_input_num += 1
         # write the input to an input file:
        input_file_name = os.path.join(self.__input_dir_name,
                                       str(self.__unique_input_num))
        input_file = self.__fho.get_file_object(input_file_name, 'w')
        input_file.write(str(inp))
        self.__fho.close_file_object(input_file)
        # write the input location to the test file:
        self.__test_file.write(
            "".join(["INPUT\n", os.path.join("ibm", input_file_name), "\n"]))

    def parse_and_generate(self):
        """Does the actual parsing and generation."""
        # read the lines from the config file:
        # open the test file:
        test_file_name = os.path.join(self.__test_name, "test.txt")
        self.__test_file = self.__fho.get_file_object(test_file_name, 'w')
        # parse all the lines, writing the corresponding stuff to the test file
        # and to key, circuit and input files:
        for line in self.__config_file_lines:
            parts = line.split(' ')
            assert(len(parts) == 3)
            assert(parts[1] == '=')
            self.__line_to_handler[parts[0]](parts[2])
        # close the test file:
        self.__fho.close_file_object(self.__test_file)
                
if __name__ == '__main__':
    parser = OptionParser(usage = ('This generates test files,'
                                   'one per argument passed to this script.'))
    # Arguments are interpreted as test names.
    (options, args) = parser.parse_args()
    for arg in args:
        config_file_name = os.path.join(arg, 'config.txt')
        config_file = open(config_file_name, 'r')
        parser_and_generator(arg, config_file,
                             fho.file_handle_object()).parse_and_generate()
        config_file.close()
