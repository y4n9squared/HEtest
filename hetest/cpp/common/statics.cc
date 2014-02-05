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
// Description:        Implementation of stuff in statics.h 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 21 May 2012   omd            Original Version
//*****************************************************************

#include "statics/ordered-function-registry.h"

#include <boost/bind.hpp>
#include <cstdlib>

using std::string;

// In order to get a reliable singleton for the finalizer and initializer
// OrderedFunctionRegistry objects we use the static function variable trick.

static OrderedFunctionRegistry* InitializerRegistry() {
  static OrderedFunctionRegistry registry; 
  return &registry;
}

static OrderedFunctionRegistry* FinalizerRegistry() {
  static OrderedFunctionRegistry registry; 
  return &registry;
}

static void RunFinalizers() {
  FinalizerRegistry()->RunFunctions();
}

void Initialize() {
  // Run all the initializer functions.
  InitializerRegistry()->RunFunctions();
  
  // Arrange to have all the finalizers run at program exit.
  atexit(&RunFinalizers);
}

bool AddInitializer(const string& name,
                    boost::function<void ()> init_function) {
  InitializerRegistry()->AddFunction(name, init_function);
  return true;
}

bool OrderInitializers(const string& first, const string& second) {
  InitializerRegistry()->OrderConstraint(first, second);
  return true;
}

bool AddFinalizer(const string& name,
                  boost::function<void ()> finalize_function) {
  FinalizerRegistry()->AddFunction(name, finalize_function);
  return true;
}

bool OrderFinalizers(const string& first, const string& second) {
  FinalizerRegistry()->OrderConstraint(first, second);
  return true;
}
