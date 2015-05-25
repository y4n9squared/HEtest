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
// Authors:            OMD
// Description:        Assert-like functions.
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 03 May 2012   omd            Original Version
//*****************************************************************

// This defines CHECK and DCHECK macros that work essentially like asserts.
// By defining our own we get more control over where the log messages go and
// such which is potentially useful.
//
// CHECK's are always performed
// DHCECK's are performed as long as NO_DCHECKS is not defined.

#ifndef CPP_COMMON_CHECK_H_
#define CPP_COMMON_CHECK_H_

#include <cstdlib>
#include <iostream>

#include "logging.h"

#ifdef NO_DEATH_ON_CHECK_FAIL
#define CHECK_STREAM ERROR
#else
#define CHECK_STREAM FATAL
#endif

#define CHECK(A) if (A) ; \
    else LOG(CHECK_STREAM) << "Check '" << #A << "' failed in " << __FILE__ \
        << " on line " << __LINE__ << "\n"

#ifdef NDEBUG
// We still need the CHECK_STREAM bit so calls to operator<< will compile but
// since there's an "if true" that does nothing the compiler should strip it
// knowing it'll never execute.
#define DCHECK(A) if (true) ; \
    else LOG(CHECK_STREAM) << "Should never execute!"
#else
#define DCHECK(A) CHECK(A)
#endif

#endif
