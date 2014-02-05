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

#ifndef MYSQL_CLIENT_TIMER_H_
#define MYSQL_CLIENT_TIMER_H_

#include <time.h>

// Getting accurate timing information is somewhat complex and system
// dependent.  This factors out the specific time fetching mechanism so we
// can easily replace it for different stystems, clocks, etc. if necerssary.
class Timer {
 public:
  Timer();
  // Call once to start the timer.
  void Start();
  // Call as many times as desired. Returns the number of seconds that have
  // elapsed since Start() was called.
  double Elapsed() const;
  // Convert a struct timespec object to a double representing a number of
  // seconds. Note that clock_gettime returns the amount of time elapsed from
  // some unspecified start point so this is not a meaningful value by itself.
  static double TimespecToDouble(timespec value);
 private:
  timespec start_;
};

#endif
