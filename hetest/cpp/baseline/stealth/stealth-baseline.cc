//*****************************************************************
// Copyright (c) 2013 Massachusetts Institute of Technology
//
// Developed exclusively at US Government expense under US Air Force contract
// FA8721-05-C-002. The rights of the United States Government to use, modify,
// reproduce, release, perform, display or disclose this computer software and
// computer software documentation in whole or in part, in any manner and for
// any purpose whatsoever, and to have or authorize others to do so, are
// Unrestricted and Unlimited.
//
// Licensed for use under the BSD License as described in the BSD-LICENSE.txt
// file in the root directory of this release.
//
// Project:            SPAR
// Authors:            Yang
// Description:        Implementation of StealthBaseline.
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 20 Sep 2012  yang            Original Version
//*****************************************************************

#include <iostream>
#include "stealth-baseline.h"
#include "stealth-circuit-parser.h"
#include "circuit.h"
#include "common/check.h"
#include "common/logging.h"

using namespace std;

StealthBaseline::StealthBaseline(StealthCircuitParser* p) : Baseline(p) {}

// Read the input into a string and evaluate on the stored circuit.
// Even though the output is unencrypted, we respond with a EDATA message
// to remain consistent with how the SUT server behaves.
void StealthBaseline::ReadInputAndEvaluate() {
  string line;
  getline(cin, line);
  int size = atoi(line.c_str());
  char input[size];
  cin.read(input, size);
  getline(cin, line);
  CHECK(line == "ENDEDATA")
      << "Received unexpected message footer from test-harness: " << line;
  //TODO(yang): the short_circuit argument is currently hard-coded
  bool output = circuit_->Evaluate(input, true);
  cout << "EDATA\n" << 1 << "\n" << output << "ENDEDATA" << endl;
}



