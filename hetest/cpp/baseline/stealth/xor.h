//****************************************************************
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
// Description:    A logical XOR gate.
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 07 Aug 2012   Yang           Original Version
//****************************************************************

#ifndef CPP_BASELINE_TA2_STEALTH_XOR_H_
#define CPP_BAsELINE_TA2_STEALTH_XOR_H_

#include "multi-input-gate.h"

// This class defines a logical XOR gate which performs a boolean
// XOR operation on all of its inputs.
class Xor : public MultiInputGate {
 public:
  virtual ~Xor() {}

 protected:
  // Returns false if all or none of its inputs are true,
  // true otherwise.
  virtual bool EvaluateImpl(bool short_circuit);
};

#endif
