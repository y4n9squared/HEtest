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
// Description:        An IBM rotation gate 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 17 Sep 2012  yang            Original Version
//*****************************************************************


#ifndef CPP_BASELINE_TA2_IBM_ROTATE_H_
#define CPP_BASELINE_TA2_IBM_ROTATE_H_

#include "unary-gate.h"

// Rotate shifts the bits with wrap around. The rotation occurs in the direction
// from least-significant-bit to most-significant-bit.
class Rotate : public UnaryGate {
 public:

  // Shift the bits in the direction from least-significant-bit to
  // most-significant-bit.
  virtual BitArray EvaluateImpl(); 

  // Rotate overloads the SetConstant method to take in integer input which
  // specifies how many bits the output is rotated by.
  void SetConstant(int c) { num_rotate_ = c; }

 private:

  // Number of bits to rotate in the direction of LSB to MSB.
  int num_rotate_;
};

#endif
