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
// Description:        Baseline to handle test-harness communication
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 25 Sep 2012  yang            Original Version
//*****************************************************************


#ifndef CPP_BASELINE_TA2_STEALTH_BASELINE_H_
#define CPP_BASELINE_TA2_STEALTH_BASELINE_H_

#include <memory>
#include "circuit-parser.h"

class Circuit;

// The Baseline class handles the communication to and from the test-harness. It
// provides methods that implement the protocol for key exchange, circuit
// injection, and evaluation.
class Baseline {

 public:

  // Start the loop which causes the Baseline to listen on stdin.
  void Start();

 protected:

  // A derived class must pass in the CircuitParser object. The Stealth baseline
  // will pass a StealthCircuitParser. The IBM baseline will pass an
  // IbmCircuitParser.
  Baseline(CircuitParser* p);

  std::auto_ptr<Circuit> circuit_;
 
 private:
  void StorePublicKey();
  void InjestCircuit();

  // Because Stealth and IBM circuits have differnent output types, the
  // implementation of this method is left for the derived class.
  // ReadInputAndEvaluate is called when the baseline recieves an EDATA message.
  // The next line on stdin is the byte size of the input. This method must
  // output the return message EDATA\nENDEDATA containing the size and output 
  // on stdout.  
  virtual void ReadInputAndEvaluate() = 0;

  std::auto_ptr<CircuitParser> parser_;
  Baseline();

};


#endif
