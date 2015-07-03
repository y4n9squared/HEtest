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
// Authors:            OMD
// Description:        Performance timing class.
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 26 Oct 2011   omd            Added this header
//*****************************************************************

#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>

class Timer {
 public:
  // Call once to start the timer.
  void Start();

  // Call as many times as desired. Returns the number of seconds that have
  // elapsed since Start() was called.
  double Elapsed() const;

 private:
  std::chrono::high_resolution_clock::time_point start_;
};

#endif
