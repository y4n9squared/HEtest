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
// Description:        Implementation of CircuitParser
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 21 Sep 2012  yang            Original Version
//*****************************************************************

#include <iostream>
#include "circuit.h"
#include "stealth-def.h"
#include "common/check.h"


using namespace std;


Circuit::Circuit(ParserState* p) : output_gate_(p->output_gate),
    wires_(p->wires) {
  delete p;
}

bool Circuit::Evaluate(const string& input, bool short_circuit) {
  output_gate_->Reset();
  Parse(input);
  return output_gate_->Evaluate(short_circuit);
}

void Circuit::Parse(const string& input) {
  unsigned int index = 0;
  // Read for bits and ignore the rest
  for (unsigned int i = 0; i < input.size(); ++i) {
    if (isdigit(input[i])) {
      char bit = input[i];
      int value = atoi(&bit);
      DCHECK(value == 0 || value == 1) << "Value is " << value << " On index " << i;
      wires_->at(index)->SetValue(value);
      ++index;
    }
  }
  DCHECK(index == wires_->size()) << "Incorrect number of inputs: " << index;
}

