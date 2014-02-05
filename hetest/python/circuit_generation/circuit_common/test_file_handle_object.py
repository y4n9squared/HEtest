
# *****************************************************************
# Copyright (c) 2013 Massachusetts Institute of Technology
#
# Developed exclusively at US Government expense under US Air Force contract
# FA8721-05-C-002. The rights of the United States Government to use, modify,
# reproduce, release, perform, display or disclose this computer software and
# computer software documentation in whole or in part, in any manner and for
# any purpose whatsoever, and to have or authorize others to do so, are
# Unrestricted and Unlimited.
#
# Licensed for use under the BSD License as described in the BSD-LICENSE.txt
# file in the root directory of this release.
#  
#  Project:            SPAR
#  Authors:            SY
#  Description:        TA2 test file handle object class
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  28 Nov 2012   SY             Original Version
# *****************************************************************

# this class is meant to handle file-like objects without modifying the file
# system, for unit testing.

import StringIO

class test_file_handle_object(object):
    """A class that overwrites all methods that write to the file system."""

    def __init__(self):
        self.__files = dict([])
        # stores files here
    
    def create_dir(self, dir_name):
        """does nothing - we don't want to create directories during unit
        testing"""
        pass
    
    def get_file_object(self, file_name, command):
        """returns a file object. command shoule be either 'r' or 'w'."""
        if command == 'r':
            # find the file in self.__files:
            return self.__files[file_name]
        elif command == 'w':
            # create a file object:
            new_file = StringIO.StringIO()
            self.__files[file_name] = new_file
            return new_file

    def close_file_object(self, file_object):
        """does nothing, since we are using StringIO as our file objects, and
        we cannot access their contents after they are closed."""
        pass

    def get_file(self, file_name):
        """returns a stored file object"""
        return self.__files[file_name]
