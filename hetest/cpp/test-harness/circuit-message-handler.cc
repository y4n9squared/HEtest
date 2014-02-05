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

#include "circuit-message-handler.h"
#include "common/check.h"

using namespace std;

CircuitMessageHandler::CircuitMessageHandler(ostream* log) 
    : MessageHandler(log) {
}

void CircuitMessageHandler::Send(istream* circuit_stream) {
  timer().Start();
  server_stdin()->Write("CIRCUIT");
  string line;
  while (circuit_stream->good()) {
    getline(*circuit_stream, line);
    if (line != "") {
      server_stdin()->Write(line);
    }
  }
  CHECK(circuit_stream->eof() == true);
  server_stdin()->Write("ENDCIRCUIT");
  
  server_stdout()->Read(&line);
  CHECK(line == "CIRCUIT") << "Expected CIRCUIT header but got " << line;
  server_stdout()->Read(&line);

  CHECK(line == "CIRCUIT READY") << "Expected CIRCUIT READY but got " << line;
  server_stdout()->Read(&line);
  CHECK(line == "ENDCIRCUIT") << "Expected ENDCIRCUIT but got " << line;
  
  double ingestion_time = timer().Elapsed();
  *log() << "INGESTION " << ingestion_time << endl;
}

