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
// Description:    A gate interface for Stealth circuits
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 29 May 2012   yang           Original Version
//****************************************************************

#ifndef CPP_BASELINE_TA2_STEALTH_GATE_H_
#define CPP_BASELINE_TA2_STEALTH_GATE_H_

#include <boost/shared_ptr.hpp>

class Gate;
typedef boost::shared_ptr<Gate> GatePtr;

// This class defines the gate interface for Stealth circuits. Stealth gates 
// take as input one or more boolean values and outputs a single boolean value 
// as the result of the operation defined by that gate.

class Gate {
 public:
  virtual ~Gate() {}

  // Evaluate performs a logical gate operation on the gate's inputs, producing 
  // a single boolean output. The boolean parameter short_circuit specifies 
  // whether the derived gate type should short circuit its evaluation once the 
  // output value is known. This parameter is only used by MultiInputGate
  // objects whose logic can be short circuited. However it is still important 
  // to pass this value through other gates so that it is propogated to children
  // until it reaches a Wire.
  virtual bool Evaluate(bool short_circuit) = 0;

  // Subclasses of Gate must implement an operation to clear their cached output
  // value. This will be called before a different input is evaluated on the 
  // same circuit.
  virtual void Reset() = 0;

  // Subclasses of Gate must implement an operation to return the number of 
  // inputs currently assigned to the gate.
  virtual int NumInputs() = 0;

  // Subclasses of Gate must implement an operation to return the gate at the
  // specified index.
  virtual GatePtr GetInput(int i) = 0;
};

#endif
