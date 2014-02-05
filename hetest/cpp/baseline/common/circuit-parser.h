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
// Description:        Flex/lemon parser wrapper
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 25 Sep 2012  yang            Original Version
//*****************************************************************


#ifndef CPP_BASELINE_TA2_COMMON_CIRCUIT_PARSER_H_
#define CPP_BASELINE_TA2_COMMON_CIRCUIT_PARSER_H_

#include <cstdlib>
#include <string>
#include <memory>

#include "baseline/common/lex-global.h"
#include "baseline/common/flex-def.h"
#include "baseline/common/lemon-def.h"

class Circuit;

// Flex and Lemon have a lot of boilerplate code. Most of it needs to be
// executed in the same way regardless of which performer we need a parser for.
// This base class consolidates the intialization and teardown code for
// Flex/Lemon in one place.
class CircuitParser {

 public:

  // The only job of the derived class is to implement how parsing works for the
  // circuit of the performer. When parsing is complete, a Circuit object is
  // returned.
  virtual std::auto_ptr<Circuit> ParseCircuit(const std::string& input) = 0;

  // This version takes no input and reads its input through stdin.
  virtual std::auto_ptr<Circuit> ParseCircuit() = 0;

  // Free the scanner and parser objects
  virtual ~CircuitParser() {
    Destroy();
  }

 protected:

  // Allocate a Flex scanner and Lemon parser
  CircuitParser() {
    Init();
  }

  YYSTYPE yylval_;
  yyscan_t scanner_;
  void* parser_ ;
  YY_BUFFER_STATE buffer_state_;

 private:

  void Init() {
    yylex_init_extra(yylval_, &scanner_);
    parser_ = ParseAlloc(malloc);
  }

  void Destroy() {
    yylex_destroy(scanner_);
    ParseFree(parser_, free);
  }



};

#endif
