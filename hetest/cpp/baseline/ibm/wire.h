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
// Description:        IBM Constant Gate 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 31 Aug 2012   yang            Original Version
//*****************************************************************


#ifndef CPP_BASELINE_TA2_CIRCUIT_EVALUATION_IBM_CONST_H_
#define CPP_BASELINE_TA2_CIRCUIT_EVALUATION_IBM_CONST_H_

#include "gate.h"
#include "common/logging.h"

// A Wire is the baseline's representation of a wire. It has no inputs and
// always outputs the same bit-array, set using the SetInput() method.
class Wire : public Gate {
 public:

  void SetInput(BitArray input) {
    SetOutput(input);
  }

  virtual BitArray Evaluate() {
    return output();
  }
 
  virtual void Reset() {}

};
typedef boost::shared_ptr<Wire> WirePtr;

#endif
