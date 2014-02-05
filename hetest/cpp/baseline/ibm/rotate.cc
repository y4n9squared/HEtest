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
// Description:        Implementation of Rotate 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 24 Sep 2012  yang            Original Version
//*****************************************************************


#include "rotate.h"

BitArray Rotate::EvaluateImpl() {
    boost::dynamic_bitset<> bits = input()->Evaluate();
    int size = bits.size();
    boost::dynamic_bitset<> rotated_bits(size);
    for (int i = 0; i < size; ++i) {
      rotated_bits[(i+num_rotate_) % size] = bits[i];
    }
    return rotated_bits;
}
