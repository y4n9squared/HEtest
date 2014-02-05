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
// Description:        Implementation of parser wrapper 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 18 Sep 2012  yang            Original Version
//*****************************************************************

#include <iostream>
#include <string>
#include "stealth-circuit-parser.h"
#include "circuit.h"
#include "stealth-def.h"
#include "common/logging.h"

using namespace std;

auto_ptr<Circuit> StealthCircuitParser::ParseCircuit(const string& input) {
  buffer_state_ = yy_scan_string(input.c_str(), scanner_);
  ParserState* parser_state = new ParserState();
  int lexcode;
  do {
    lexcode = yylex(scanner_);
    Parse(parser_, lexcode, yyget_extra(scanner_), parser_state);
  } while (lexcode > 0);
  if (lexcode == -1) {
      LOG(FATAL) << "Scanner encountered error";
  }
  yy_delete_buffer(buffer_state_, scanner_);
  return auto_ptr<Circuit> (new Circuit(parser_state));
}

auto_ptr<Circuit> StealthCircuitParser::ParseCircuit() {
  ParserState* parser_state = new ParserState();
  int lexcode;
  do {
    lexcode = yylex(scanner_);
    Parse(parser_, lexcode, yyget_extra(scanner_), parser_state);
  } while (lexcode > 0);
  if (lexcode == -1) {
      LOG(FATAL) << "Scanner encountered error";
  }
  return auto_ptr<Circuit> (new Circuit(parser_state));
}
