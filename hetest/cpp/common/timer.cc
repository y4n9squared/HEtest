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
// Description:        implementation of Timer class.
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 26 Oct 2011   omd            Added this header
//*****************************************************************

#include "timer.h"

#include <iostream>

using namespace std;

const clockid_t CLOCK_TO_USE = CLOCK_MONOTONIC;

Timer::Timer() {
}

void Timer::Start() {
  clock_gettime(CLOCK_TO_USE, &start_);
}

double Timer::TimespecToDouble(timespec value) {
  const int NumNanoSecondsPerSecond = 1e9;
  double ret = value.tv_sec +
    static_cast<double>(value.tv_nsec) /
    static_cast<double>(NumNanoSecondsPerSecond);
  return ret;
}


double Timer::Elapsed() const {
  timespec end;
  clock_gettime(CLOCK_TO_USE, &end);
  double start_sec = TimespecToDouble(start_);
  double end_sec = TimespecToDouble(end);
  return end_sec - start_sec;
}
