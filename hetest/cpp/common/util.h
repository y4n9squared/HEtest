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
// Description:        Various utilites. 
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 29 May 2012   omd            Original Version
//*****************************************************************


#ifndef CPP_COMMON_UTIL_H_
#define CPP_COMMON_UTIL_H_

#include <ext/stdio_filebuf.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Standard C++ doesn't provide any way to create an iostream object from a file
// handle. But many useful functions (e.g. exec and pipe) return file handles
// and don't have C++ equivalents. This class and FileHandleIStream convert a
// file handle into an iostream object. They do this using g++ extensions that
// may not be available on other platforms.
class FileHandleOStream : public std::ostream {
 public:
  // Construct a output stream for the file handle given by fd.
  FileHandleOStream(int fd);
  virtual ~FileHandleOStream() {}
  // Close the output stream.
  void close();
 private:
  // This is a g++ extension - it's a filebuf that's constructed from a file
  // handle.
  __gnu_cxx::stdio_filebuf<char> buf_;
  int fd_;
};

// VERY similar to FileHandleOStream. See that class for details.
//
// Unfortunately, there's just enough difference that we can't easily create a
// base class and then an istream and an ostream subclass. Differences include
// the argument passed to the buf_ constructor and the fact that you need to
// flush() an ostream before closing but you can't flush an istream.
class FileHandleIStream : public std::istream {
 public:
  FileHandleIStream(int fd);
  virtual ~FileHandleIStream() {}
  void close();
 private:
  __gnu_cxx::stdio_filebuf<char> buf_;
  int fd_;
};

// Spawning a child process in C++ is a huge pain - especially if you want to
// connect iostreams to stdin and stdout of the process. This function takes
// care of all the ugliness.
//
// Arguments:
//   executable: Path to the binary to run
//   args: vector of arguments to pass to the executable
//   process_stdin: on return this will hold a pointer to an ostream. Writing to
//      stream sends data to the process' stdin.
//   process_stdout: on return this holds a pointer to an istream. Reading from
//      this stream retreives input from the process' stdout.
void SpawnAndConnectPipes(
    const std::string& executable, const std::vector<std::string>& args,
    std::auto_ptr<FileHandleOStream>* process_stdin,
    std::auto_ptr<FileHandleIStream>* process_stdout);

// Overloaded version of the above but takes all the arguments as one long
// string.
void SpawnAndConnectPipes(
    const std::string & executable, const std::string& args,
    std::auto_ptr<FileHandleOStream>* process_stdin,
    std::auto_ptr<FileHandleIStream>* process_stdout);

// Another overloaded version which returns file handles instead of
// FileHandle*Stream objects
void SpawnAndConnectPipes(
    const std::string& executable, const std::vector<std::string>& args,
    int* process_stdin_handle, int* process_stdout_handle);

// And another version! This one returns file handles and takes the args as a
// string instead of a vector<string>.
void SpawnAndConnectPipes(
    const std::string& executable, const std::string& args,
    int* process_stdin_handle, int* process_stdout_handle);

// Many low-level C-library calls set errno if there is an error. This returns a
// string that contains a text represenation of the error.
std::string ErrorMessageFromErrno(int errnum);


#endif
