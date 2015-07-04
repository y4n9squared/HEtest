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
// Description:        Executes a key-exchange round with the SUT
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 26 Sep 2012   yang           Original Version
//*****************************************************************

#ifndef TEST_HARNESS_KEY_MESSAGE_HANDLER_H_
#define TEST_HARNESS_KEY_MESSAGE_HANDLER_H_

#include "message-handler.h"

// The KeyMessageHandler implements the communication protocol for key exchange
// with the SUT client.
class KeyMessageHandler : public MessageHandler {
 public:
  // Constructor takes as input the result log stream.
  KeyMessageHandler(std::ostream* log);

  // This method implements the actual communication protocol. It takes as input
  // the security parameter and wait for the expected response. The method
  // transmits the public key from the client to the server.
  virtual void Send(std::istream* is);
};
#endif
