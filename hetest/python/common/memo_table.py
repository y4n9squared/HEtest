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
#  Description:        An implementation of a memo table. 
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  02 Feb 2012   omd            Original Version
# *****************************************************************

class MemoTable(dict):
    """A MemoTable is a simple caching mechanism to speed up repeated
    computations. You construct one with a function that computes a value for
    given key. Then you use it like a regular dictionary. The first time a value
    is requested it is computed using the function supplied to the constructor.
    All subsequent calls simply return the value from the cache. For example:

    def factorial(x):
        if x == 1:
            return 1
        return x * factorial(x-1)

    mt = MemoTable(factorial)

    x1 = mt[100]  # This computes, and returns 100!
    x2 = mt[100]  # This just looks up the value from the pervious call
    assert x1 == x2
    """
    def __init__(self, compute_fun):
        """Constructs a MemoTable that computes the value for key x by calling
        compute_fun(x)."""
        assert callable(compute_fun)
        self.__comput_fun = compute_fun
        self.__values = {}

    def __getitem__(self, key):
        if not key in self:
            value = self.__comput_fun(key)
            super(MemoTable, self).__setitem__(key, value)
            return value
        else:
            return super(MemoTable, self).__getitem__(key)

    def __setitem__(self, key, value):
        raise TypeError('MemoTable does not support assignement')
