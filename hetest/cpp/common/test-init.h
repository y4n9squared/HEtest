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
// Description:        All unit tests should #include this to initialize any
//                     statics, etc. 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 25 May 2012   omd            Original Version
//*****************************************************************

// This initializes statics, #include boost's unit test stuff and #defines the
// right macro, before boost unit test #inclusion, to have the test dynamically
// linked against the boost unit test runner and it's main() function.


#ifndef CPP_COMMON_TEST_INIT_H_
#define CPP_COMMON_TEST_INIT_H_

#include "statics.h"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

// Perform simple initialization
class InitTest {
 public:
   InitTest() { Initialize(); }
  ~InitTest() {}
};

BOOST_GLOBAL_FIXTURE(InitTest);

#endif
