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
// Description:    A boolean NOT gate for Stealth circuits.
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 29 May 2012   yang           Original Version
//****************************************************************

#ifndef CPP_BASELINE_TA2_STEALTH_NOT_H_
#define CPP_BASELINE_TA2_STEALTH_NOT_H_

#include <boost/shared_ptr.hpp>
#include "gate.h"
#include "common/check.h"

// This class defines a boolean NOT gate for Stealth circuits. A NOT gate 
// contains a single input gate and outputs the negated value of its
// input.
class Not : public Gate {
 public:

  // The constructor takes the shared_ptr to the input of the Not gate. We do
  // this instead of defining an AddInput() method like other gates because Not
  // gates in Stealth syntax appear recursively within other gates.
  Not(GatePtr input) : input_(input) {}
  virtual ~Not() {}

  // Return the negated input.
  virtual bool Evaluate(bool short_circuit) { 
    return !input_->Evaluate(short_circuit); 
  }

  // The output to a Not gate is not cached, so just calls
  // Reset() on its input gate.
  virtual void Reset() { input_->Reset(); }

  // Not gate only has single input. Return 1.
  virtual int NumInputs() { return 1; }

  virtual GatePtr GetInput(int i) {
    CHECK(i==0) << "Attempting to access invalid index into a Not gate.";
    return input_;
  }

 private:
  Not();
  GatePtr input_;
  bool output_;
};

#endif
