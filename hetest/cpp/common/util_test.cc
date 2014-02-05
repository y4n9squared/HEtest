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
// Description:        Unit tests for util.h 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 29 May 2012   omd            Original Version
//*****************************************************************

#include "util.h"

#include <boost/assign/list_of.hpp>
#include <cstdlib>
#include <fstream>
#include <memory>

#define BOOST_TEST_MODULE UtilTest

#include "test-init.h"

using namespace std;

BOOST_AUTO_TEST_CASE(FileHandleOStreamWorks) {
  char tempfile[] = "/tmp/unit_test_XXXXXX";
  int fd = mkstemp(tempfile);
  FileHandleOStream output_stream(fd);

  output_stream << "Line 1\n" << "Line 2\n";
  output_stream.close();

  ifstream instream(tempfile);
  string line;
  getline(instream, line);
  BOOST_CHECK_EQUAL(line, "Line 1");
  getline(instream, line);
  BOOST_CHECK_EQUAL(line, "Line 2");

  getline(instream, line);
  BOOST_CHECK_EQUAL(line.size(), 0);
  BOOST_CHECK_EQUAL(instream.eof(), true);
}

BOOST_AUTO_TEST_CASE(SpawnWorks) {
  // Spawn 'wc' and write some data to it. Make sure the output is as expected.
  auto_ptr<FileHandleOStream> process_stdin;
  auto_ptr<FileHandleIStream> process_stdout;
  vector<string> args;
  SpawnAndConnectPipes("/usr/bin/wc", args, &process_stdin, &process_stdout);

  *process_stdin << "Line 1\nLine 2\n";
  process_stdin->close();

  string output;
  cout << "Calling getline" << endl;
  getline(*process_stdout, output);
  BOOST_CHECK_EQUAL(output, "      2       4      14");
}
