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
// Description:        
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 25 Sep 2012  yang            Original Version
//*****************************************************************

#include <string>
#include <iostream>
#include "baseline.h"
#include "common/logging.h"
#include "common/check.h"

using namespace std;

Baseline::Baseline(CircuitParser* p) 
  : parser_(std::auto_ptr<CircuitParser>(p)) {
}

void Baseline::InjestCircuit() {
  circuit_ = parser_->ParseCircuit();
  cout << "CIRCUIT\nCIRCUIT READY\nENDCIRCUIT" << endl;
}

void Baseline::StorePublicKey() {
  string line;
  while(line != "ENDKEY") {
    getline(cin, line);
  }
}

// Listen on stdin
void Baseline::Start() {
  string line;
  while (getline(cin, line)) {
    if (line == "KEY") {
      StorePublicKey();
    } else if (line == "CIRCUIT") {
      InjestCircuit();
    } else if (line == "EDATA") {
      ReadInputAndEvaluate();
    } else {
      LOG(FATAL) << "Unexpected input on baseline's stdin: " << line;
    }
  }
}
