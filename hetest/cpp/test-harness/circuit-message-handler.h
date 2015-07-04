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
// Description:        Sends a circuit description to the SUT server
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 26 Sep 2012  yang            Original Version
//*****************************************************************

#ifndef TEST_HARNESS_CIRCUIT_MESSAGE_HANDLER_H_
#define TEST_HARNESS_CIRCUIT_MESSAGE_HANDLER_H_

#include "test-harness/message-handler.h"

// CircuitMessageHandler implements the communication protocol for passing the
// circuit description and public key to the SUT server.
class CircuitMessageHandler : public MessageHandler {
 public:
  CircuitMessageHandler(std::ostream* log);

  // This method implements the actual communication protocol. It takes as input
  // an input stream which contains the circuit description. The circuit
  // description should follow the syntax outlined in the test plan. The method
  // will read in the circuit and send the message
  //
  // CIRCUIT
  // <circuit description>
  // ENDCIRCUIT
  // KEY
  // <public key>
  // ENDKEY
  //
  // and wait for a CIRCUIT READY message from the server.
  virtual void Send(std::istream* circuit_stream);
};

#endif
