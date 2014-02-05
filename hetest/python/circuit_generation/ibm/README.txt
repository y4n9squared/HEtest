Firstly, make sure that 
(1) your current directory is circuit_generation/ibm, and 
(2) that you have python 2.7 installed.
You can then type the following to the command line:
python ibm_generate.py TEST_NAME

TEST_NAME should be the name of a directory.
The corresponding directory will be populated with test 
circuits, inputs, and security parameters. Generation will take place based 
on the 'config.txt' file in the corresponding directory. The config file 
will contain text of the following format:

seed = 1234567890
test_type = RANDOM
num_circuits = 2
num_inputs = 5
K = 80
L = 682
D = 24
W = 200
generate = True
L = 1285
D = 60
W = 50
generate = True

The above instructs that for each of (L = 682, D = 24, W = 200) and
(L = 1285, D = 60, W = 50), 2 circuits with gate types chosen at random, 
each with 5 corresponding inputs, be created. \
The randomness seed 1234567890 is used.
Generation takes place when 'generate = True' appears.
The parameters are as follows:
seed (the random number generator is seeded with this value - can be omitted)
test_type (should be 'random' (meaning gate types are chosen at random) for the
           large circuit, varying parameter, and additional tests, and should be
           all of 'LADD', 'LADDconst', 'LMUL', 'LMULconst', 'LSELECT' 
           and 'LROTATE' for the single gate type test.
K (the security parameter - should be specified for all tests)
L (the batch size - should be specified for all tests)
D (the depth of the circuit, as defined by IBM - should be specified for the
   large circuit, varying parameter, and additional tests.)
num_levels (the number of levels in the circuit - should be specified instead
            of D for single gate type test)
W (the number of gates possible at each level - should be specified for all
   tests)
num_circuits (the number of circuits to create for each parameter setting -
              should be specified for all tests)
num_inputs (the number of inputs to create for each circuit - should be
            specified for each parameter setting)

In order to modify the sets of circuits created for each test, modify the
config.txt files in the directories corresponding to the tests before running
'python ibm_generate.py test_directory_name'.