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
// Description:        A dummy client for harness testing
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 26 Sep 2012   yang           Original Version
//*****************************************************************

#include <cstdlib>
#include <iostream>
#include <string>

#include "common/statics.h"
#include "common/check.h"

// This is a really dumb baseline client. It simply outputs a public key of 0,
// echos the unencrypted input as encrypted output, and echos the encrypted
// result as unencrypted result.
int main(int argc, const char* argv[]) {
  Initialize();
  std::string line;
  while (getline(std::cin, line)) {
    if (line == "KEY") {
      // consume the security param
      getline(std::cin, line);
      while (line != "ENDKEY") {
        getline(std::cin, line);
      }
      CHECK(line == "ENDKEY") << "Unexpected key message footer" << line;
      // return the public key
      std::cout << "KEY\n0\nENDKEY" << std::endl;
    } else if (line == "PDATA") {
      std::string input;
      // consume the plain-text input
      getline(std::cin, input);
      CHECK(line.size() > 0) << "Did not receive an input";
      // consume the message footer
      getline(std::cin, line);
      CHECK(line == "ENDPDATA") << "Unexpected PDATA footer" << line;
      std::cout << "EDATA\n" << input.size() << "\n";
      std::cout.write(input.c_str(), input.size());
      std::cout << "ENDEDATA" << std::endl;
    } else if (line == "EDATA") {
      std::string temp;
      // consume encrypted-data
      getline(std::cin, temp);
      CHECK(temp.size() > 0) << "Did not receive an encrypted output";
      int size = std::stoul(temp);
      char output[size];
      std::cin.read(output, size);
      // consume the message footer
      getline(std::cin, line);
      CHECK(line == "ENDEDATA") << "Unexpected EDATA footer" << line;
      std::cout << "PDATA\n";
      std::cout.write(output, size);
      std::cout << "\nENDPDATA" << std::endl;
    }
  }
  return 0;
}
