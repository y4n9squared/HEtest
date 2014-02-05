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
// Description:        Baseline representation of a Stealth circuit
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 19 Sep 2012   yang           Original Version
//*****************************************************************


#ifndef CPP_BASELINE_TA2_STEALTH_CIRCUIT_H_
#define CPP_BASELINE_TA2_STEALTH_CIRCUIT_H_

#include <vector>
#include <string>
#include "stealth-circuit-gates.h"

class ParserState;
class CircuitParser;

// A Circuit object is collection of gates that represent an actual boolean 
// circuit. It supports a single operation Evaluate(), which returns the output
// of a circuit given its inputs. 
class Circuit {

 public:
  // Evaluates the circuit given the specified input and returns its boolean
  // value. 
  //
  // input_str: a string of bits of the form: [0, 1, 0, 1, 0, 0]
  //
  // where the bit of the i-th index of this array is the value corresponding to
  // the i-th input wire of the circuit.
  //
  // short_circuit: boolean parameter which determines whether or not the
  // circuit will short-circuit. If true, the circuit will return its output
  // immediately after it knows its value. 
  bool Evaluate(const std::string& input_str, bool short_circuit);

 private:

  // The constructor is called exclusively by a CircuitParser object.
  // A Circuit takes ownership of ParserState.
  Circuit(ParserState* p);
  friend class StealthCircuitParser;

  void Parse(const std::string& input_str);

  boost::shared_ptr<Gate> output_gate_;
  std::auto_ptr< std::vector<WirePtr> > wires_;

};

#endif
