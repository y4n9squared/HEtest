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
// Description:        Unit tests for the logging stuff. 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 16 May 2012   omd            Original Version
//*****************************************************************

#define BOOST_TEST_MODULE LoggingTest

#include "logging.h"

#include <sstream>

#include "test-init.h"

using std::stringstream;

// Tests that basic logging, where all logs end up in the same same log file,
// work as expected.
BOOST_AUTO_TEST_CASE(SingleFileLogPolicyWorks) {
  stringstream output;
  Log::SetOutputStream(&output);

  LOG(DEBUG) << "Message 1";
  LOG(INFO) << "Message 2";
  LOG(WARNING) << "Message 3";
  LOG(ERROR) << "Message 4";


  Log::SetApplicationLogLevel(WARNING);

  LOG(DEBUG) << "Should not be logged";
  LOG(INFO) << "Should not be logged either";
  LOG(WARNING) << "Message 5";
  LOG(ERROR) << "Message 6";

  // Now change the log level via preprocessor. That should cause all log
  // messages below ERROR to not even be compiled in!
#undef MIN_LOG_LEVEL
#define MIN_LOG_LEVEL 3
  LOG(DEBUG) << "Not Logged";
  LOG(INFO) << "Not Logged";
  LOG(WARNING) << "Not Logged";
  LOG(ERROR) << "Message 7";

  stringstream expected;
  expected << "[DEBUG] Message 1\n"
           << "[INFO] Message 2\n"
           << "[WARNING] Message 3\n"
           << "[ERROR] Message 4\n"
           << "[WARNING] Message 5\n"
           << "[ERROR] Message 6\n"
           << "[ERROR] Message 7\n";

  BOOST_CHECK_EQUAL(output.str(), expected.str());
}
