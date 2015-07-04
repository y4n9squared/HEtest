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
// Description:        Unit tests for KeyMessageHandler
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 26 Sep 2012  yang            Original Version
//*****************************************************************

#include "test-harness/key-message-handler.h"

#include <memory>
#include <sstream>
#include <string>

#define BOOST_TEST_MODULE
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "common/test-init.h"
#include "test-harness/stream-util.h"

BOOST_AUTO_TEST_CASE(KeyHandlerWorks) {
  auto client_stdin_pipe = new std::stringstream();
  auto client_stdout_pipe = new std::stringstream();
  auto server_stdin_pipe = new std::stringstream();
  auto server_stdout_pipe = new std::stringstream();

  std::unique_ptr<std::stringstream> client_stdin_ptr(client_stdin_pipe);
  std::unique_ptr<std::stringstream> client_stdout_ptr(client_stdout_pipe);
  std::unique_ptr<std::stringstream> server_stdin_ptr(server_stdin_pipe);
  std::unique_ptr<std::stringstream> server_stdout_ptr(server_stdout_pipe);
  std::unique_ptr<std::stringstream> results(new std::stringstream());

  TestHarnessIStream client_stdout(std::move(client_stdout_ptr));
  TestHarnessOStream client_stdin(std::move(client_stdin_ptr));
  TestHarnessIStream server_stdout(std::move(server_stdout_ptr));
  TestHarnessOStream server_stdin(std::move(server_stdin_ptr));

  auto k = KeyMessageHandler(results.get());
  k.set_client_stdin(&client_stdin);
  k.set_client_stdout(&client_stdout);
  k.set_server_stdin(&server_stdin);
  k.set_server_stdout(&server_stdout);

  // Write the expected client response. This is done before the client actually
  // gets the securit parameter but for testing that's okay. Ideally, the
  // client's response is run in a separate thread.
  *client_stdout_pipe << "KEY\npublic_key\nENDKEY" << std::endl;

  std::stringstream file;
  file << "security parameters";
  k.Send(&file);

  BOOST_CHECK_EQUAL(client_stdin_pipe->str(),
                    "KEY\nsecurity parameters\nENDKEY\n");
  BOOST_CHECK_EQUAL(client_stdout_pipe->str(), "KEY\npublic_key\nENDKEY\n");
  BOOST_CHECK_EQUAL(server_stdin_pipe->str(), "KEY\npublic_key\nENDKEY\n");
  BOOST_CHECK(results->str().find("KEYGEN") != std::string::npos);
}
