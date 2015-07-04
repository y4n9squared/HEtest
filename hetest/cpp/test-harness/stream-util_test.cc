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
// Description:        Unit tests for StreamUtil
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 26 Sep 2012   yang            Original Version
//*****************************************************************

#include "test-harness/stream-util.h"

#include <istream>
#include <memory>
#include <ostream>
#include <sstream>

#define BOOST_TEST_MODULE
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "common/test-init.h"

BOOST_AUTO_TEST_CASE(TestHarnessOStreamWorks) {

  auto sut = new std::stringstream();
  std::unique_ptr<std::ostream> ofs(sut);
  TestHarnessOStream output_stream(std::move(ofs));

  auto log = new std::stringstream();
  std::unique_ptr<std::ostream> logger(log);
  output_stream.SetDebugLogStream(std::move(logger), true);

  output_stream.Write("HELLO\nWORLD");
  const char* buf = "Hello World";
  output_stream.Write(buf, 11);

  BOOST_CHECK_EQUAL(sut->str(), "HELLO\nWORLD\nHello World");
  BOOST_CHECK_EQUAL(log->str(), "HELLO\nWORLD\nHello World");
}

BOOST_AUTO_TEST_CASE(TestHarnessIStreamWorks) {

  auto sut = new std::stringstream();
  auto log = new std::stringstream();

  *sut << "FOO\nBAR" << std::endl;
  const char* buf = "Foo bar";
  sut->write(buf, 7);

  std::unique_ptr<std::istream> ifs(sut);
  TestHarnessIStream input_stream(std::move(ifs));
  std::unique_ptr<std::ostream> logger(log);
  input_stream.SetDebugLogStream(std::move(logger), true);

  std::string line;
  input_stream.Read(&line);
  BOOST_CHECK_EQUAL(line, "FOO");
  input_stream.Read(&line);
  BOOST_CHECK_EQUAL(line, "BAR");
  char input_buf[8];
  input_stream.Read(input_buf, 7);
  input_buf[7] = '\0';
  BOOST_CHECK_EQUAL(buf, "Foo bar");
  BOOST_CHECK_EQUAL(log->str(), "FOO\nBAR\nFoo bar");
}
