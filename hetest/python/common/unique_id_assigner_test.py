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
#  Description:        Unit tests for uniqe id assigner 
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  12 Jan 2012   omd            Original Version
# *****************************************************************

from unique_id_assigner import UniqueIdAssigner
import unittest

class UniqueIdAssignerTest(unittest.TestCase):
    def test_basic(self):
        ua = UniqueIdAssigner()
        self.assertEqual(ua.insert('hello'), 0)
        self.assertEqual(ua.insert('world'), 1)
        self.assertEqual(ua.insert('oliver'), 2)
        self.assertEqual(ua.get_id('world'), 1)
        self.assertEqual(ua.get_id('oliver'), 2)
        self.assertEqual(ua.get_key(2), 'oliver')
        self.assertEqual(ua.get_key(0), 'hello')
