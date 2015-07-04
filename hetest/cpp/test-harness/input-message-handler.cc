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
// Description:        Implementation of InputMessageHandler
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 26 Sep 2012  yang            Original Version
//*****************************************************************

#include "test-harness/input-message-handler.h"

#include <chrono>
#include <string>

#include "common/check.h"

InputMessageHandler::InputMessageHandler(std::ostream* log)
    : MessageHandler(log) {}

void InputMessageHandler::Send(std::istream* input_stream) {
  auto start = std::chrono::high_resolution_clock::now();
  std::string line;
  client_stdin()->Write("PDATA");
  while (input_stream->good()) {
    getline(*input_stream, line);
    if (line != "") {
      client_stdin()->Write(line);
    }
  }
  CHECK(input_stream->eof());
  client_stdin()->Write("ENDPDATA");

  // We expect an EDATA message from the client.
  client_stdout()->Read(&line);
  CHECK(line == "EDATA") << "Got '" << line << "'";
  client_stdout()->Read(&line);
  unsigned int size = stoul(line);
  char encrypted_input[size];
  client_stdout()->Read(encrypted_input, size);
  client_stdout()->Read(&line);
  CHECK(line == "ENDEDATA") << "Got '" << line << "'";
  auto encrypt_time = std::chrono::duration_cast<std::chrono::duration<double>>(
      std::chrono::high_resolution_clock::now() - start);
  *log() << "ENCRYPT " << encrypt_time.count() << std::endl;
  std::stringstream msg_stream;
  msg_stream << "EDATA\n" << size;
  start = std::chrono::high_resolution_clock::now();
  server_stdin()->Write(msg_stream.str());
  server_stdin()->Write(encrypted_input, size);
  server_stdin()->Write("ENDEDATA");

  // We expect an EDATA message from the server
  server_stdout()->Read(&line);
  CHECK(line == "EDATA") << "Got '" << line << "'";
  server_stdout()->Read(&line);
  size = stoul(line);
  char encrypted_output[size];
  server_stdout()->Read(encrypted_output, size);
  server_stdout()->Read(&line);
  CHECK(line == "ENDEDATA") << "Got '" << line << "'";
  auto eval_time = std::chrono::duration_cast<std::chrono::duration<double>>(
      std::chrono::high_resolution_clock::now() - start);
  *log() << "EVALUATION " << eval_time.count() << std::endl;

  std::stringstream result_msg_stream;
  result_msg_stream << "EDATA\n" << size;
  start = std::chrono::high_resolution_clock::now();
  client_stdin()->Write(result_msg_stream.str());
  client_stdin()->Write(encrypted_output, size);
  client_stdin()->Write("ENDEDATA");

  // We expect a PDATA message from the client.
  client_stdout()->Read(&line);
  CHECK(line == "PDATA") << "Got '" << line << "'";
  client_stdout()->Read(&line);
  *log() << "RESULT " << line << std::endl;
  client_stdout()->Read(&line);
  CHECK(line == "ENDPDATA") << "Got '" << line << "'";
  auto decrypt_time = std::chrono::duration_cast<std::chrono::duration<double>>(
      std::chrono::high_resolution_clock::now() - start);
  *log() << "DECRYPT " << decrypt_time.count() << std::endl;
}
