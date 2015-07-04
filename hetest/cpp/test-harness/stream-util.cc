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
// Description:        Implementation of TestHarnessXStream
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 15 Oct 2012  yang            Original Version
//*****************************************************************

#include "test-harness/stream-util.h"

#include <istream>
#include <memory>
#include <ostream>
#include <string>

#include "common/check.h"

TestHarnessIStream::TestHarnessIStream(std::unique_ptr<std::istream> stream)
    : stream_{std::move(stream)}, debug_stream_{}, buffered_{true} {}

void TestHarnessIStream::Read(std::string* line) {
  getline(*stream_, *line);
  if (debug_stream_.get() != nullptr) {
    if (!buffered_)
      *debug_stream_ << *line << std::endl;
    else
      *debug_stream_ << *line << '\n';
  }
}

bool TestHarnessIStream::good() const { return stream_->good(); }

void TestHarnessIStream::Read(char* buf, unsigned int size) {
  stream_->read(buf, size);
  if (debug_stream_.get() != nullptr) {
    debug_stream_->write(buf, size);
    if (!buffered_) debug_stream_->flush();
  }
}

void TestHarnessIStream::SetDebugLogStream(
    std::unique_ptr<std::ostream> debug_stream, bool buffered) {
  CHECK(debug_stream.get() != nullptr);
  debug_stream_ = move(debug_stream);
  buffered_ = buffered;
}

TestHarnessOStream::TestHarnessOStream(std::unique_ptr<std::ostream> stream)
    : stream_{std::move(stream)}, debug_stream_{}, buffered_{true} {}

void TestHarnessOStream::Write(const std::string& line) {
  *stream_ << line << std::endl;
  if (debug_stream_.get() != nullptr) {
    if (!buffered_)
      *debug_stream_ << line << std::endl;
    else
      *debug_stream_ << line << '\n';
  }
}

void TestHarnessOStream::Write(const char* buf, unsigned int size) {
  stream_->write(buf, size);
  if (debug_stream_.get() != nullptr) {
    debug_stream_->write(buf, size);
    if (!buffered_) debug_stream_->flush();
  }
}

void TestHarnessOStream::SetDebugLogStream(
    std::unique_ptr<std::ostream> debug_stream, bool buffered) {
  CHECK(debug_stream.get() != nullptr);
  debug_stream_ = move(debug_stream);
  buffered_ = buffered;
}
