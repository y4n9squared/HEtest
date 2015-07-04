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
// Description:        Implementation of KeyMessageHandler
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 26 Sep 2012  yang            Original Version
//*****************************************************************

#include "test-harness/key-message-handler.h"

#include <chrono>
#include <string>

#include "common/check.h"

KeyMessageHandler::KeyMessageHandler(std::ostream* log) : MessageHandler(log) {}

void KeyMessageHandler::Send(std::istream* is) {
  auto start = std::chrono::high_resolution_clock::now();
  client_stdin()->Write("KEY");
  std::string line;
  while (is->good()) {
    getline(*is, line);
    if (line != "") {
      client_stdin()->Write(line);
    }
  }
  CHECK(is->eof());
  client_stdin()->Write("ENDKEY");

  client_stdout()->Read(&line);
  CHECK(line == "KEY") << "Got '" << line << "'";
  server_stdin()->Write("KEY");
  while (line != "ENDKEY") {
    client_stdout()->Read(&line);
    server_stdin()->Write(line);
  }
  CHECK(line == "ENDKEY") << "Got '" << line << "'";
  auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(
      std::chrono::high_resolution_clock::now() - start);
  *log() << "KEYGEN " << elapsed_time.count() << std::endl;
}
