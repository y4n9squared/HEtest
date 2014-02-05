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
// Description:        Select gate
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 17 Sep 2012  yang            Original Version
//*****************************************************************


#ifndef CPP_BASELINE_TA2_IBM_SELECT_H_
#define CPP_BASELINE_TA2_IBM_SELECT_H_

#include "binary-gate.h"
#include "common/logging.h"

// Select takes as input two Gates and a constant BitArray. Each bit in the
// BitArray specifies which bit in the two input Gates goes to the output. For
// example: Select(Gate1, Gate2, [1,1,0,0]) says to take the first and second
// bits of Gate1 and the third and fourth bits of Gate2.
class Select : public BinaryGate {
 public:
  virtual BitArray EvaluateImpl() {
    return (constant() & left_input()->Evaluate()) 
        | (~constant() & right_input()->Evaluate());
  }
};

#endif
