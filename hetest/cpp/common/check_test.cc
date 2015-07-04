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
// Description:        Unit tests for the functions in check.h
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 03 May 2012   omd            Original Version
//*****************************************************************

#define BOOST_TEST_MODULE CheckTest

#include <iostream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

#include "logging.h"
#include "test-init.h"

#define NO_DEATH_ON_CHECK_FAIL

#include "check.h"

using boost::regex_search;
using boost::regex;

BOOST_AUTO_TEST_CASE(CheckBasic) {
  std::stringstream test_stream;
  Log::SetOutputStream(&test_stream);
  // Simplest failing check I could think of.
  CHECK(false);
  // Check that the error message has the expected format.
  regex expected_re(
      "Check 'false' failed in .*check_test.cc on line \\d+");
  BOOST_CHECK(regex_search(test_stream.str(), expected_re));

  // Check a slightly more complicated test.
  test_stream.str("");
  CHECK(7 == 11);
  expected_re = "Check '7 == 11' failed in .*check_test.cc on line \\d+";
  BOOST_CHECK(regex_search(test_stream.str(), expected_re));
}

// Since NDEBUG is not defined DCHECK should work exactly the same way as
// CHECK
#ifndef NDEBUG
BOOST_AUTO_TEST_CASE(DCheckBasic) {
  std::stringstream test_stream;
  Log::SetOutputStream(&test_stream);
  // Simplest failing check I could think of.
  DCHECK(false);
  // Check that the error message has the expected format.
  regex expected_re(
      "Check 'false' failed in .*check_test.cc on line \\d+");
  BOOST_CHECK(regex_search(test_stream.str(), expected_re));

  // Check a slightly more complicated test.
  test_stream.str("");
  CHECK(7 == 11);
  expected_re = "Check '7 == 11' failed in .*check_test.cc on line \\d+";
  BOOST_CHECK(regex_search(test_stream.str(), expected_re));

}
#endif

// Make sure you can use a CHECK as an output stream.
BOOST_AUTO_TEST_CASE(CheckAsStream) {
  std::stringstream test_stream;
  Log::SetOutputStream(&test_stream);

  CHECK(false) << "This is my output: " << 22;
  std::vector<std::string> lines;
  std::string test_stream_str = test_stream.str();
  boost::split(lines, test_stream_str, boost::is_any_of("\n"));
  BOOST_REQUIRE_EQUAL(lines.size(), 3);
  regex expected_line_1_re(
      "Check 'false' failed in .*check_test.cc on line \\d+");
  BOOST_CHECK(regex_search(lines[0], expected_line_1_re));
  BOOST_CHECK_EQUAL(lines[1], "This is my output: 22");
  BOOST_CHECK_EQUAL(lines[2], "");
}
