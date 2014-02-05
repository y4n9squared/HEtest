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
#  Authors:            OMD
#  Description:        Wraps cPickle.load so you can iterate through
#                      a file of pickled objects.
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  18 Apr 2012   omd            Original Version
# *****************************************************************

import cPickle

class PickleIter(object):
    def __init__(self, file_obj):
        self.__file = file_obj

    def __iter__(self):
        return self.generate()

    def generate(self):
        while True:
            try:
                obj = cPickle.load(self.__file)
                yield obj
            except EOFError, e:
                break
            
