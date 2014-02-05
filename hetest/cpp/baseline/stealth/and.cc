//****************************************************************
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
// Description:        Implementation of AND gate
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 29 May 2012   yang           Original Version
//****************************************************************

#include "and.h"
#include "common/check.h"

bool And::EvaluateImpl(bool short_circuit) {
  CHECK(NumInputs() >= 2) << "Not enough inputs";
  bool value = true;
  for (int i = 0; i < NumInputs(); ++i) {
    if (!GetInput(i)->Evaluate(short_circuit)) {
      value = false;
      if (short_circuit) {
        return value;
      }
    }
  }
  return value;
}
