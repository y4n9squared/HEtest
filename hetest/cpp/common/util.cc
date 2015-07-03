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
// Description:        Implementation of util methods.
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 29 May 2012   omd            Original Version
//*****************************************************************

#include "util.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <unistd.h>

#include "logging.h"
#include "string-algo.h"

FileHandleOStream::FileHandleOStream(int fd)
    : std::ostream(&fpstream_), fpstream_(fd, io::close_handle) {
}

void FileHandleOStream::close() {
  flush();
}

FileHandleIStream::FileHandleIStream(int fd)
    : std::istream(&fpstream_), fpstream_(fd, io::close_handle) {
}

// This is pretty much the standard unix fork/exec thing plus we set up file
// handles for the subprocess' stdin/stdout.
void SpawnAndConnectPipes(
    const std::string& executable, const std::vector<std::string>& args,
    int* process_stdin_handle, int* process_stdout_handle) {
  // File descriptors for the pipe that the parent writes to to send data tot he
  // child and the pipe the child writes to to send data to the parent.
  int parent_to_child[2];
  int child_to_parent[2];

  // Calling pipe returns two file descriptors. These constants indicate which
  // file descriptor is for reading and which is for writing.
  const int READ_END = 0;
  const int WRITE_END = 1;

  // We're going to connect the pipes to the child's stdin and stdout. These are
  // the file descriptors for those streams.
  const int STDIN_FD = 0;
  const int STDOUT_FD = 1;

  if (pipe(parent_to_child) < 0) {
    LOG(ERROR) << "Error creating pipe!";
    exit(1);
  }
  if (pipe(child_to_parent) < 0) {
    LOG(ERROR) << "Error creating pipe!";
    exit(1);
  }

  int pid = fork();
  if (pid < 0) {
    LOG(ERROR) << "Fork failed!";
    exit(1);
  }

  if (pid == 0) {
    // child process

    // Close the ends of the pipe we won't use.
    close(parent_to_child[WRITE_END]);
    close(child_to_parent[READ_END]);

    // Redirect the pipe to stdin/stdout and then close the pipe file handles.
    dup2(parent_to_child[READ_END], STDIN_FD);
    close(parent_to_child[READ_END]);
    dup2(child_to_parent[WRITE_END], STDOUT_FD);
    close(child_to_parent[WRITE_END]);

    // execv requires a 0-terminated array of char*. The 1st argument must be
    // the name of the executable. Here we build that array.
    char** exec_args = new char*[args.size() + 2];
    exec_args[0] = new char[executable.size() + 1];
    strcpy(exec_args[0], executable.c_str());
    for (unsigned int i = 0; i < args.size(); ++i) {
      exec_args[i + 1] = new char[args[i].size() + 1];
      strcpy(exec_args[i+1], args[i].c_str());
    }
    exec_args[args.size() + 1] = 0;
    execv(executable.c_str(), exec_args);
    // Note that exec_args memory is never freed, but after the call to execv
    // this process is reaped so there's no real leak and no way to clean it up
    // even if there was a leak.
  } else {
    // parent process

    // Close the ends of the pipe we won't use.
    close(parent_to_child[READ_END]);
    close(child_to_parent[WRITE_END]);

    *process_stdout_handle = child_to_parent[READ_END];
    *process_stdin_handle = parent_to_child[WRITE_END];
  }
}


void SpawnAndConnectPipes(
    const std::string& executable, const std::vector<std::string>& args,
    std::auto_ptr<FileHandleOStream>* process_stdin,
    std::auto_ptr<FileHandleIStream>* process_stdout) {
  int stdin_h, stdout_h;
  SpawnAndConnectPipes(executable, args, &stdin_h, &stdout_h);
  // Wrap the ends that are connected to stdin/stdout with a iostream.
  process_stdout->reset(new FileHandleIStream(stdout_h));
  process_stdin->reset(new FileHandleOStream(stdin_h));
}

void SpawnAndConnectPipes(
    const std::string & executable, const std::string& args,
    std::auto_ptr<FileHandleOStream>* process_stdin,
    std::auto_ptr<FileHandleIStream>* process_stdout) {
  std::vector<std::string> args_vec;
  Split(args, ' ', &args_vec);
  SpawnAndConnectPipes(executable, args_vec, process_stdin, process_stdout);
}

void SpawnAndConnectPipes(
    const std::string& executable, const std::string& args,
    int* process_stdin_handle, int* process_stdout_handle) {
  std::vector<std::string> args_vec;
  Split(args, ' ', &args_vec);
  SpawnAndConnectPipes(executable, args_vec, process_stdin_handle,
                       process_stdout_handle);
}

std::string ErrorMessageFromErrno(int errnum) {
  const int kBufferSize = 1024;
  char buffer[kBufferSize];
  strerror_r(errnum, buffer, kBufferSize);
  return std::string(buffer);
}
