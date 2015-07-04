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
// Description:        Unit tests for CircuitMessageHandler
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 26 Sep 2012  yang            Original Version
//*****************************************************************

#include "circuit-message-handler.h"

#include <memory>
#include <string>
#include <sstream>

#define BOOST_TEST_MODULE
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "common/test-init.h"

BOOST_AUTO_TEST_CASE(CircuitHandlerWorks) {
  auto server_stdin_ptr =
      std::unique_ptr<std::stringstream>(new std::stringstream());
  auto server_stdin_handle = server_stdin_ptr.get();
  TestHarnessOStream server_stdin(std::move(server_stdin_ptr));

  auto server_stdout_ptr =
      std::unique_ptr<std::stringstream>(new std::stringstream());
  auto server_stdout_handle = server_stdout_ptr.get();
  TestHarnessIStream server_stdout(std::move(server_stdout_ptr));

  std::auto_ptr<std::stringstream> results(new std::stringstream());

  auto c = CircuitMessageHandler(results.get());
  c.set_server_stdin(&server_stdin);
  c.set_server_stdout(&server_stdout);

  *server_stdout_handle << "CIRCUIT\nCIRCUIT READY\nENDCIRCUIT" << std::endl;

  std::stringstream file;
  file << "This\nIs\nA\nCircuit";
  c.Send(&file);

  BOOST_CHECK_EQUAL(server_stdin_handle->str(),
                    "CIRCUIT\nThis\nIs\nA\nCircuit\nENDCIRCUIT\n");
  BOOST_CHECK_EQUAL(server_stdout_handle->str(),
                    "CIRCUIT\nCIRCUIT READY\nENDCIRCUIT\n");
  BOOST_CHECK(results->str().find("INGESTION") != std::string::npos);
}
