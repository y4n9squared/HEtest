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
// Description:        Main executable to start the TA2 test harness 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 19 Sep 2012   yang            Original Version
//*****************************************************************i

#include <string>
#include <vector>
#include <fstream>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include "test-script.h"
#include "common/logging.h"
#include "common/util.h"
#include "common/check.h"
#include "common/statics.h"

using namespace std;
namespace po = boost::program_options;

int main(int argc, char** argv) {
  Initialize();
  string server, client, debug_log;
  po::variables_map vm;
  try {
    po::options_description desc("Options");
    desc.add_options()
      ("help,h", "print help message")
      ("server,s", po::value<string>(&server)->required(), 
       "Path to server executable")
      ("server_args,a", po::value<string>()->default_value(""),
       "Arguments to pass to the SUT server")
      ("client_args,b", po::value<string>()->default_value(""),
       "Arguments to pass to the SUT client")
      ("client,c", po::value<string>(&client)->required(), 
       "path to client executable")
      ("debug,d", po::value<string>(), 
       "debug mode. If a string is specified, the stdin and stdout of the "
       "client and server will be captured to four log files, whose file "
       "names start with the string and end in _client_stdin, _client_stdout, "
       "_server_stdin,and _server_stdout")
      ("recovery,r", "Resumes a test script at the most recent crash, as "
       "indicated in the recoery log")
      ("test,t", po::value<string>()->required(), "path to test script");

    po::positional_options_description p;
    p.add("test", -1);

    po::store(po::command_line_parser(argc, argv).options(desc).
            positional(p).run(), vm);

    if (vm.count("help")) {
      cout << desc << endl;
      exit(0);
    }
    po::notify(vm);
  } catch (exception& e) {
    cerr << "Error parsing command line arguments: " << e.what() << endl;
  } catch(...) {
    cerr << "Unknown exception parsing command line arguments!" << endl;
  }

  TestScript script;
  ofstream* log = new ofstream("results");
  script.SpawnClient(client, vm["client_args"].as<string>());
  script.SpawnServer(server, vm["server_args"].as<string>());
  script.RegisterHandler(TestScript::KEY_DELIM, new KeyMessageHandler(log));
  script.RegisterHandler(
      TestScript::CIRCUIT_DELIM, new CircuitMessageHandler(log));
  script.RegisterHandler(TestScript::INPUT_DELIM, new InputMessageHandler(log));
  script.InitHandlers();

  if (vm.count("debug")) {
    script.SetDebugLogStream(vm["debug"].as<string>());
  }
  if (vm.count("recovery")) {
    script.Resume(vm["test"].as<string>());
  } else {
    script.Execute(vm["test"].as<string>());
  }
}
