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
// Description:    A logical OR gate.
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 29 May 2012   yang           Original Version
//****************************************************************

#ifndef CPP_BASELINE_TA2_STEALTH_OR_H_
#define CPP_BASELINE_TA2_STEALTH_OR_H_

#include "multi-input-gate.h"

// This class defines a logical OR gate which performs a
// boolean OR operation o nall of its inputs.
class Or : public MultiInputGate {
 public:
  virtual ~Or() {}

 protected:
  // Returns TRUE if one or more inputs are TRUE, FALSE otherwise.
  virtual bool EvaluateImpl(bool short_circuit);
};

#endif
