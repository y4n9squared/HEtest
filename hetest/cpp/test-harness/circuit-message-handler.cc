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
// Description:        Implementation of CircuitMessageHandler
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 26 Sep 2012  yang            Original Version
//*****************************************************************

#include "test-harness/circuit-message-handler.h"

#include <chrono>
#include <string>

#include "common/check.h"

CircuitMessageHandler::CircuitMessageHandler(std::ostream* log)
    : MessageHandler(log) {}

void CircuitMessageHandler::Send(std::istream* circuit_stream) {
  auto start = std::chrono::high_resolution_clock::now();
  server_stdin()->Write("CIRCUIT");
  std::string line;
  while (circuit_stream->good()) {
    getline(*circuit_stream, line);
    if (line != "") {
      server_stdin()->Write(line);
    }
  }
  CHECK(circuit_stream->eof());
  server_stdin()->Write("ENDCIRCUIT");

  server_stdout()->Read(&line);
  CHECK(line == "CIRCUIT") << "Expected 'CIRCUIT'. Got '" << line << "'";
  server_stdout()->Read(&line);

  CHECK(line == "CIRCUIT READY") << "Expected 'CIRCUIT READY'. Got '" << line
                                 << "'";
  server_stdout()->Read(&line);
  CHECK(line == "ENDCIRCUIT") << "Expected 'ENDCIRCUIT'. Got '" << line << "'";

  auto ingestion_time =
      std::chrono::duration_cast<std::chrono::duration<double>>(
          std::chrono::high_resolution_clock::now() - start);
  *log() << "INGESTION " << ingestion_time.count() << std::endl;
}
