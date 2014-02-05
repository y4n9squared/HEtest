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
#  Description:        A dictionary with a default value 
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  14 Dec 2011   omd            Original Version
# *****************************************************************

class DefaultDict(dict):
    """Like a regular dictionary but there's a default value for anything not
    in the dictionary. This is particularly handy for keeping counts of things
    with a dict as it allows you to replace this code:

    d = {}
    for i in items_we_are_counting:
        if i in d:
            d[i] += 1
        else:
            d[i] = 1

    with this code:

    d = DefaultDict(0)
    for i in items_we_are_counting:
        d[i] += 1

    See the unit tests in default_dict_test.py to get a full sense of the
    semantics."""
    def __init__(self, default_value, *args, **kwargs):
        """You must supply default_value, the value that will be returned for
        any item not in the dictionary. All other arguments are passed
        directly through to the regular dict constructor and behave as they
        normally would."""
        super(DefaultDict, self).__init__(*args, **kwargs)
        self.__default = default_value

    def __getitem__(self, key):
        """If the key is in the dictionary return it. Otherwise return the
        default value passed to the constructor."""
        if not key in self:
            return self.__default

        return super(DefaultDict, self).__getitem__(key)

