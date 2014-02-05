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
// Project:        SPAR
// Authors:        Yang
// Description:    Implementation of MultiInputGate.
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 10 June 2012  yang           Original Version
//****************************************************************

#include "multi-input-gate.h"
#include "common/check.h"

void MultiInputGate::AddInput(GatePtr input) {
  inputs_.push_back(input);
}

GatePtr MultiInputGate::GetInput(int i) {
  return inputs_[i];
}

bool MultiInputGate::Evaluate(bool short_circuit) {
  if (evaluated_) {
    // output is cached
    return output_;
  }
  output_ = EvaluateImpl(short_circuit);
  evaluated_ = true;
  return output_;
}

void MultiInputGate::Reset() {
  if (evaluated_) {
    for (unsigned int i = 0; i < inputs_.size(); ++i) {
      inputs_[i]->Reset();
    }
    evaluated_ = false;
  }
}

int MultiInputGate::NumInputs() {
  return inputs_.size();
}
