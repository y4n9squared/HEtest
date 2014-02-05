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
// Description:        Various string processing algorithms. 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 09 May 2012   omd            Original Version
//*****************************************************************

#ifndef CPP_COMMON_STRING_ALGO_H_
#define CPP_COMMON_STRING_ALGO_H_

#include <string>
#include <vector>

// Split source into pieces by delimited. Return those pieces by appending them
// to result.
void Split(const std::string& source, char delimiter,
           std::vector<std::string>* result);

// Overloaded version of the above Split. May be less efficient as the compiler
// may not be smart enough to avoid copying the entire vector into the result.
inline std::vector<std::string> Split(const std::string& source,
                                      char delimiter) {
  std::vector<std::string> result;
  Split(source, delimiter, &result);
  return result;
}

void Join(const std::vector<std::string>& data, const std::string& delim,
                 std::string* result);

inline std::string Join(
    const std::vector<std::string>& data, const std::string& delim) {
  std::string result;
  Join(data, delim, &result);
  return result;
}

// Just like strdup in <cstring> but uses operator new[] to allocate the new
// string instead of malloc. This is sometimes important since operator delete
// shouldn't be used with memory that was allocated via malloc.
char* StrDup(const char* src);

// Like the common, but non-standard, itoa function, this returns a string
// representation of an integer.
std::string itoa(int x);

// Like atoi or strtol but safe. This converts it's argument to an int and CHECK
// fails if the passed string does not consist soley of an integer value.
int SafeAtoi(const std::string& data);

// Same as the above, but outputs a long long instead of an int
long long SafeAtoll(const std::string& data);

// Converts a string to all uppercase. The conversion happens in-place.
void ToUpper(std::string* str);

// Converts a string to all lowercase. The conversion happens in-place.
void ToLower(std::string* str);

#endif
