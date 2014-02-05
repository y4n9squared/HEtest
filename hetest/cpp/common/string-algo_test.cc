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
// Description:        Unit tests for the string algorithms. 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 09 May 2012   omd            Original Version
//*****************************************************************

#include "string-algo.h"

#define BOOST_TEST_MODULE StringAlgoTest

#include <boost/assign/list_of.hpp>
#include <limits>
#include <string>
#include <vector>

#include "test-init.h"

using std::string;
using std::vector;

BOOST_AUTO_TEST_CASE(SplitWorks) {
  vector<string> t1 = Split("No delimiter", ',');
  BOOST_REQUIRE_EQUAL(t1.size(), 1);
  BOOST_CHECK_EQUAL(t1[0], "No delimiter");

  vector<string> t2 = Split("a,b,c", ',');
  BOOST_REQUIRE_EQUAL(t2.size(), 3);
  BOOST_CHECK_EQUAL(t2[0], "a");
  BOOST_CHECK_EQUAL(t2[1], "b");
  BOOST_CHECK_EQUAL(t2[2], "c");

  vector<string> t3 = Split("long 1\nlonger length 2\n\nfoo", '\n');
  BOOST_REQUIRE_EQUAL(t3.size(), 4);
  BOOST_CHECK_EQUAL(t3[0], "long 1");
  BOOST_CHECK_EQUAL(t3[1], "longer length 2");
  BOOST_CHECK_EQUAL(t3[2], "");
  BOOST_CHECK_EQUAL(t3[3], "foo");

  vector<string> t4 = Split(",,", ',');
  BOOST_REQUIRE_EQUAL(t4.size(), 3);
  BOOST_CHECK_EQUAL(t4[0], "");
  BOOST_CHECK_EQUAL(t4[1], "");
  BOOST_CHECK_EQUAL(t4[2], "");
}

BOOST_AUTO_TEST_CASE(ToUpperWorks) {
  string s1("abcDEFghizZQm");
  ToUpper(&s1);
  BOOST_CHECK_EQUAL(s1, "ABCDEFGHIZZQM");

  // Note: the @`[{ characters are the ascii codes just before and after a, z,
  // A, and Z so these are good edge cases.
  string s2("za$%mn!.?@`[{hello");
  ToUpper(&s2);
  BOOST_CHECK_EQUAL(s2, "ZA$%MN!.?@`[{HELLO");
}

BOOST_AUTO_TEST_CASE(ToLowerWorks) {
  string s1("ABcdeFGH ijKLm");
  ToLower(&s1);
  BOOST_CHECK_EQUAL(s1, "abcdefgh ijklm");

  string s2(" @#$*ZAmk@#4AA");
  ToLower(&s2);
  BOOST_CHECK_EQUAL(s2, " @#$*zamk@#4aa");
}

BOOST_AUTO_TEST_CASE(JoinWorks) {
  vector<string> data;
  data.push_back("Long part 1");
  data.push_back("p2");
  data.push_back("and part 3");

  BOOST_CHECK_EQUAL(Join(data, ","), "Long part 1,p2,and part 3");
  BOOST_CHECK_EQUAL(Join(data, " BIGDELIM "),
                    "Long part 1 BIGDELIM p2 BIGDELIM and part 3");
}

// This checks that SafeAtoi can convert valid values. It does *not* check that
// it crashes the program on invalid values. We should add that but we require
// death tests to do it.
//
// TODO(odain) Add death tests that ensure SafeAtoi crashes on bad input. See
// bug #789.
BOOST_AUTO_TEST_CASE(SafeAtoiWorks) {
  vector<int> test_values = boost::assign::list_of(-1)(0)(1)(100)(-285)(372)
                                           (std::numeric_limits<int>::min())
                                           (std::numeric_limits<int>::max());

  for (vector<int>::const_iterator i = test_values.begin();
       i != test_values.end(); ++i) {
    string str_value = itoa(*i);
    BOOST_CHECK_EQUAL(SafeAtoi(str_value), *i);
  }

  // And just to double check, we'll manually check a few of these in case atoi
  // is doing something weird.
  BOOST_CHECK_EQUAL(SafeAtoi("-118"), -118);
  BOOST_CHECK_EQUAL(SafeAtoi("0"), 0);
  BOOST_CHECK_EQUAL(SafeAtoi("1"), 1);
  BOOST_CHECK_EQUAL(SafeAtoi("83"), 83);
}
