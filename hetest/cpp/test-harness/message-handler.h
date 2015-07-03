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
// Description:        Base class for message handlers
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 09 Nov 2012  yang            Original Version
//*****************************************************************


#ifndef CPP_TEST_HARNESS_TA2_MESSAGE_HANDLER_H_
#define CPP_TEST_HARNESS_TA2_MESSAGE_HANDLER_H_

#include <iostream>
#include "stream-util.h"
#include "common/timer.h"

// MessageHandler is the base class for KeyMessageHandler,
// CircuitMessageHandler, and InputMessageHandler. It contains the pointers to
// the stdin and stdout pipes to the SUT client and server. It also holds the
// pointer to the result log and the timer.
//
// Subclasses need to implement the Send() method, which takes an input stream
// containing the data to be sent to either the SUT client or server.
class MessageHandler {

 public:

  // Constructor sets the result log.
  MessageHandler(std::ostream* log) : log_(log) {
  }

  virtual ~MessageHandler() = default;

  // Send must implement the specific protocol for either key-exchange, circuit
  // ingestion, or evaluation. Subclasses are responsible for writing the the
  // result log and keeping track of timing information using the timer provided
  // in this class.
  virtual void Send(std::istream* s) = 0;

  inline void set_client_stdin(TestHarnessOStream* client_stdin) {
    client_stdin_ = client_stdin;
  }

  inline void set_client_stdout(TestHarnessIStream* client_stdout) {
    client_stdout_ = client_stdout;
  }

  inline void set_server_stdin(TestHarnessOStream* server_stdin) {
    server_stdin_ = server_stdin;
  }

  inline void set_server_stdout(TestHarnessIStream* server_stdout) {
    server_stdout_ = server_stdout;
  }

  inline TestHarnessOStream* client_stdin() {
    return client_stdin_;
  }

  inline TestHarnessIStream* client_stdout() {
    return client_stdout_;
  }

  inline TestHarnessOStream* server_stdin() {
    return server_stdin_;
  }

  inline TestHarnessIStream* server_stdout() {
    return server_stdout_;
  }

  inline Timer& timer() {
    return timer_;
  }

  inline std::ostream* log() {
    return log_;
  }

 private:

  TestHarnessOStream* client_stdin_;
  TestHarnessIStream* client_stdout_;
  TestHarnessOStream* server_stdin_;
  TestHarnessIStream* server_stdout_;
  std::ostream* log_;
  Timer timer_;

};
#endif
