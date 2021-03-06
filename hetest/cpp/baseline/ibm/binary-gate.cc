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
// Description:        Implementation of BinaryGate 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 24 Aug 2012   yang           Original Version
//*****************************************************************

#include "binary-gate.h"
#include "common/check.h"

void BinaryGate::AddLeftInput(boost::shared_ptr<Gate> input) {
  CHECK(input != NULL) << "Attempting to assign a null input";
  left_input_ = input;
}

void BinaryGate::AddRightInput(boost::shared_ptr<Gate> input) {
  CHECK(input != NULL) << "Attempting to assign a null input";
  right_input_ = input;
}

BitArray BinaryGate::Evaluate() {
  if (evaluated_) {
    return output();
  } else {
    BitArray output = EvaluateImpl();
    SetOutput(output);
    evaluated_ = true;
    return output;
  }
}
