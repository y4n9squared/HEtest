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
// Description:        Wrapper for lemon parser
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 22 Sep 2012  yang            Original Version
//*****************************************************************


#ifndef CPP_BASELINE_TA2_IBM_CIRCUIT_PARSER_H_
#define CPP_BASELINE_TA2_IBM_CIRCUIT_PARSER_H_

#include <string>
#include <memory>
#include "baseline/common/circuit-parser.h"

class Circuit;

class IbmCircuitParser : public CircuitParser {
 public:
  // Takes a string in the form of the IBM circuit grammar syntax. Returns a
  // Circuit object that corresponds to the specified string.
  virtual std::auto_ptr<Circuit> ParseCircuit(const std::string& input);

  // Reads the circuit description from stdin and parses it. Stops reading when
  // the scanner hits a linefeed. The circuit description should contain no
  // linefeed characters before the end.
  virtual std::auto_ptr<Circuit> ParseCircuit();
};


#endif
