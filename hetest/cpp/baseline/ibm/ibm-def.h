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
// Description:        Auxilliary structs used by the lemon parser
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 22 Sep 2012  yang            Original Version
//*****************************************************************


#ifndef CPP_BASELINE_TA2_IBM_IBM_DEF_H_
#define CPP_BASELINE_TA2_IBM_IBM_DEF_H_

#include "ibm-circuit-gates.h"

struct ParserState {
  boost::shared_ptr<Gate> output_gate;
  std::vector<WirePtr>* wires;
  int length;
};

struct InputToken {
  int type;
  const char* str_val;
  int int_val;
};

struct GateToken {
  Gate* gate;
};

struct BitsToken {
  BitArray* bits;
};

#endif
