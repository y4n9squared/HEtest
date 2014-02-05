Firstly, make sure that 
(1) your current directory is circuit_generation/stealth, and 
(2) that you have python 2.7 installed.
You can then type the following to the command line:
python stealth_generate.py TEST_NAME

TEST_NAME can be 'large', 'varying_param', or 'single_gate_type', or any
other directory that contains a config.txt file.
The corresponding directory will be populated with test 
circuits, inputs, security parameters, and outputs, based on the config.txt
file. 

config.txt should contain text of the following format:
    seed = 1234567890    fam = 2    test_type = AND    K = 80    W = 20    G = 200    fg = .5    X = 300    fx = .5    num_circuits = 2    num_inputs = 5
    generate = True
The above instructs that 2 circuits consisting entirely of and gates should
be created with the parameters fam = 2, W = 20, G = 20, fg = .5, X = 300, 
and fx = .5, and that 5 inputs should be generated for each such circuit.
The randomness seed 12345 is used.

The parameters are as follows:
seed (the random number generator is seeded with this value - can be omitted)
fam (the circuit family - should be specified for all tests)
test_type (should be RANDOM (meaning gate types are chosen at random) for the
           large circuit and varying parameter tests, and should be
           all of AND, OR, and XOR for the single gate type test.
K (the security parameter - should be specified for all tests)
W (the number of input wires - should be specified for all tests)
G (the number of intermediate gates - should be specified for the
   large circuit and varying parameter tests.)
fg (the intermediate fanning fraction - should be specified instead
   for the large and varying parameter tests.)
X (the number of xor gates - should be specified for the
   large circuit and varying parameter tests.)
fx (the xor fanning fraction - should be specified instead
   for the large and varying parameter tests.)
D (the circuit depth - should be specified for the single gate type tests)
num_circuits (the number of circuits to create for each parameter setting -
              should be specified for all tests)
num_inputs (the number of inputs to create for each circuit - should be
            specified for each parameter setting)

In order to modify the sets of circuits created for each test, modify the
config.txt files in the directories corresponding to the tests before running
'python stealth_generate.py test_directory_name'.