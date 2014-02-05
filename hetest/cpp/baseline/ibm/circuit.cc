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
// 23 Sep 2012  yang            Original Version
//*****************************************************************

#include "circuit.h"
#include "common/check.h"
#include "common/string-algo.h"

using namespace std;

BitArray Circuit::Evaluate(const string& input) {
  output_gate_->Reset();
  Parse(input);
  return output_gate_->Evaluate();
}

void Circuit::Parse(const string& input) {
  unsigned int wire_index = 0;
  int bit_index = 0;
  BitArray bitset(length_);
  // Read for bits and ignore the rest
  for (unsigned int i = 0; i < input.size(); ++i) {
    if (input[i] == '1' || input[i] == '0') {
      if (input[i] == '1')
        bitset[bit_index] = 1;
      if (input[i] == '0')
        bitset[bit_index] = 0;
      ++bit_index;
      if (bit_index == length_) {
        wires_->at(wire_index)->SetInput(bitset);
        DCHECK(wires_->at(wire_index)->Evaluate() == bitset);
        ++wire_index;
        bitset.reset();
        bit_index = 0;
      }
    }
  }
  CHECK(wire_index == wires_->size()) << "Wire index is " << wire_index 
      << ". Expected " << wires_->size();
}

