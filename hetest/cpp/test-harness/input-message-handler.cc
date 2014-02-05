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

#include "input-message-handler.h"
#include "common/check.h"
#include "common/string-algo.h"

using namespace std;

InputMessageHandler::InputMessageHandler(ostream* log)
    : MessageHandler(log) {
    }

void InputMessageHandler::Send(std::istream* input_stream) {
  string line; 
  timer().Start();
  client_stdin()->Write("PDATA");
  while (input_stream->good()) {
    getline(*input_stream, line);
    if (line != "") {
      client_stdin()->Write(line);
    }
  }
  CHECK(input_stream->eof() == true);
  client_stdin()->Write("ENDPDATA");

  // We expect an EDATA message from the client.
  client_stdout()->Read(&line);
  CHECK(line == "EDATA") 
      << " Received unexpected input message header from client: " << line;
  client_stdout()->Read(&line);
  unsigned int size = SafeAtoi(line);
  char encrypted_input[size];
  client_stdout()->Read(encrypted_input, size);
  client_stdout()->Read(&line);
  CHECK(line == "ENDEDATA") 
      << "Received unexpected input message footer from client: " << line;
  double encrypt_time = timer().Elapsed();
  *log() << "ENCRYPT " << encrypt_time << endl;
  stringstream msg_stream;
  msg_stream << "EDATA\n" << size;
  timer().Start();
  server_stdin()->Write(msg_stream.str());
  server_stdin()->Write(encrypted_input, size);
  server_stdin()->Write("ENDEDATA");

  // We expect an EDATA message from the server
  server_stdout()->Read(&line);
  CHECK(line == "EDATA") 
      << "Received unexpected input message header from server: " << line;
  server_stdout()->Read(&line);
  size = SafeAtoi(line);
  char encrypted_output[size];
  server_stdout()->Read(encrypted_output, size);
  server_stdout()->Read(&line);
  CHECK(line == "ENDEDATA") 
      << "Received unexpected input message footer from server: " << line;
  double eval_time = timer().Elapsed();
  *log() << "EVALUATION " << eval_time << endl;

  stringstream result_msg_stream;
  result_msg_stream << "EDATA\n" << size;
  timer().Start();
  client_stdin()->Write(result_msg_stream.str());
  client_stdin()->Write(encrypted_output, size);
  client_stdin()->Write("ENDEDATA");

  // We expect a PDATA message from the client.
  client_stdout()->Read(&line);
  CHECK(line == "PDATA") << "Unexpected input message header: " << line;
  client_stdout()->Read(&line);
  *log() << "RESULT " << line << endl;
  client_stdout()->Read(&line);
  CHECK(line == "ENDPDATA") << "Unexpected input message footer " << line;
  double decrypt_time = timer().Elapsed();
  *log() << "DECRYPT " << decrypt_time << endl;
}

