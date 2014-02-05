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
// Description:        Stealth circuit parser
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 18 Sep 2012  yang            Original Version
//*****************************************************************


#ifndef CPP_BASELINE_TA2_STEALTH_CIRCUIT_PARSER_H_
#define CPP_BASELINE_TA2_STEALTH_CIRCUIT_PARSER_H_

#include <string>
#include <memory>
#include <istream>

#include "baseline/common/circuit-parser.h"

class Circuit;

class StealthCircuitParser : public CircuitParser {
 public:
  // Parses the description of a Stealth circuit given as a string and returns
  // a Circuit object matching the description. For more information on the
  // specific syntax of the circuit description, refer to the Test Plan.
  virtual std::auto_ptr<Circuit> ParseCircuit(const std::string& input);

  // Parses the description of a Stealth circuit given on stdin and returns
  // a Circuit object matching the description.
  virtual std::auto_ptr<Circuit> ParseCircuit();
};

#endif
