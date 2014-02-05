HEtest
======

HEtest comprises several tools that aid in the testing and evaluation of
homomorphic encryption schemes. First, HEtest includes a **circuit generator**
that creates circuits with a given width, depth, and batch size over a given
set of gates. Second, HEtest includes a **test harness** that can drive any
software implementing homomorphic encryption and instrument its performance.
Finally, HEtest includes a **baseline** that evaluates such circuits without any
homomorphic encryption for comparison purposes.

MIT Lincoln Laboratory developed HEtest for use during the testing and
evaluation of the IARPA SPAR project, and thus the circuit generation and
baseline include some features that are specialized for SPAR submissions.
Nevertheless, the tools in HEtest are extensible and can easily be used to test
other homomorphic encryption schemes as well.

Quick Links
-----------

- [MIT Lincoln Laboratory Project Homepage](http://www.ll.mit.edu/mission/cybersec/softwaretools/hetest/hetest.html)
- [HElib - Homomorphic encryption library](https://github.com/shaih/HElib)

Introduction
------------

In order to evaluate homomorphic encryption schemes for the IARPA SPAR project,
MIT Lincoln Laboratory has built the following:

1. A test harness capable of executing the server and client executables for a
   homomorphic encryption scheme. The inputs to the test harness are the paths
   to: the server executable, the client executable, and the test script. The
   harness spawns the server and client, and then it iteratively feeds them key
   generation, circuit ingestion, encryption, homomorphic evaluation, and
   decryption requests. The key generation, encryption, and decryption requests
   are sent to the client, whereas the circuit ingestion and homomorphic
   evaluation requests are sent to the server.  The order and contents of these
   requests are spelled out by a test script.

2. A circuit generator capable of generating circuits randomly from the
   families supported by IBM and Stealth, respectively.

3. A baseline that parses and evaluates the circuits described in (2), but
   without homomorphic encryption. In fact, the baseline is able to play the
   role of the server in all five protocols described in (1).

4. A dummy client that is able to respond to requests made to it by the test
   harness. Its requests are meaningless (for instance, it always responds to
   "key" messages with "0", rather than providing a legitimate public key).
   The purpose of the dummy client is to allow Lincoln's baseline to be
   executed on the test harness in the role of the "server."

Note that all of these tools can either be used directly or augmented in a
reasonably straightforward way to support testing for new homomorphic
encryption schemes that were not part of the SPAR project.

There are two ways to utilize Lincoln's software: either use our pre-built
binaries, or compile the code yourself. The latter option will give you more
flexibility, particularly if you wish to change some feature of our code to
support your own testing.

Making Circuits
---------------

In order to build new circuits, you can run our circuit generator using the
`generate_all.sh` scripts located in `hetest/python/circuit_generation/ibm` and
`hetest/python/circuit_generation/stealth`. Stealth circuits can be much larger
in size (up to tens of gigabytes) and take much longer to generate than the IBM
ones.

If you instead want to generate only a few circuits, you can use the
stealth_generate.py or ibm_generate.py commands in these directories, or just
open the generate_all.sh file and delete the lines that you don't want.

Eventually, you may wish to augment our circuit generator tools to create
circuits of your own. The circuit generation tools are written in Python, and
they are located in /hetest/python. The circuit generators have several
tunable parameters.  Please read the following README files to get a detailed
explanation of these parameters and how to alter them to your needs:

- hetest/python/circuit_generation/ibm/README.txt
- hetest/python/circuit_generation/stealth/README.txt


Building the Test Harness and Baselines
--------------------------------------

If you are more adventurous and would like to compile our code from scratch or
augment it to add new features, this sections will explain how to build the
test harness and baseline.

### Prerequisites

All of the test harness, baseline, and dummy client code is written in C++ and
located in hetest/cpp. You will likely need the following programs/libraries to
compile the code:

- g++
- scons
- lemon
- flex
- libevent-dev
- libboost-all-dev

If you are using Ubuntu Server 12.04 (as Lincoln is), you can install any of
these with the following command:

```
sudo apt-get install <package-name>
```

### Compiling and running unit tests

Run `scons` from the cpp root `hetest/cpp` or `scons -u` from any subdirectory. To
compile a release build, pass the flags `--opt`. You may also enable valgrind
and/or gprof using the optional flags `--valgrind` and `--gprof`.

To run all unit tests, pass the optional argument `cpp_test`. You should see no
failures (although some tests will fail on very rare occasions due to random
number generation).

**NOTE**: The first time you run scons, you may see an error message like this:

```
scons: *** [hetest/cpp/baseline/ibm/opt/unary-gate.o] Error 4
os.chdir('hetest/cpp/baseline/stealth/opt')
scons: building terminated because of errors.
```

If you get an error, don't worry; just compile again and it will
work the second time.
 
The binary executables are (from the source root):
 
- TEST HARNESS:     cpp/test-harness/opt/test-harness
- DUMMY CLIENT:     cpp/test-harness/opt/dummy-client
- IBM BASELINE:     cpp/baseline/ibm/ibm-baseline-main
- STEALTH BASELINE: cpp/baseline/stealth/stealth-baseline-main

### Running the test-harness
 
To run the test-harness, run

``` 
./test-harness –s <baseline> –c <client> –t <test-script>
```

specifying the path to the baseline, client, and test script, respectively. The
test scripts are created during circuit generation. For a complete list of
options, run the test-harness with the help flag `-h`.

The results of the test will be written to a file called "results" in the
current directory. Optionally, specify `–d <debug-file-name>` to have the
test-harness write out 4 log files corresponding to the stdin/out of the
client/server, or specify `–r` to have the test harness recover from a previous
crash (and thus continue with the circuit under test at the time of the crash,
rather than starting over).

We strongly suggest that you run the test-harness with the `-h` flag the first
time you use it, as it will then print out a help screen.


Contributors
------------

* Oliver Dain
* Nick Hwang
* Sophia Yakoubov
* Yang Yang

Contact: HEtest@ll.mit.edu
