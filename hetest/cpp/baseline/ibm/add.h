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
// Description:        An IBM addition gate 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 17 Sep 2012  yang            Original Version
//*****************************************************************


#ifndef CPP_BASELINE_TA2_IBM_ADD_H_
#define CPP_BASELINE_TA2_IBM_ADD_H_

#include "binary-gate.h"

class Add : public BinaryGate {
 public:
  // Returns the bit-wise XOR operation of its left and right inputs
  virtual BitArray EvaluateImpl() {
    return left_input()->Evaluate() ^ right_input()->Evaluate();
  }
};

#endif
