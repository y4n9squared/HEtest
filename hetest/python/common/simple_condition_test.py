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
#  Description:        Unit tests for SimpleCondition 
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  04 Apr 2012   omd            Original Version
# *****************************************************************


import unittest
import threading
from simple_condition import SimpleCondition
import time

class SimpleConditionTest(unittest.TestCase):
    def test_simple_bool(self):
        cond = SimpleCondition(False)
        self.assertEqual(cond.get(), False)

        def set_true():
            time.sleep(0.5)
            cond.set(True)

        threading.Thread(target = set_true).start()

        cond.wait(True)
        self.assertEqual(cond.get(), True)

    def test_simple_integer(self):
        cond = SimpleCondition(10)
        self.assertEqual(cond.get(), 10)

        # If we wait until its 10 and its already 10 it should return
        # immediately.
        cond.wait(10)
        self.assertEqual(cond.get(), 10)

        def set_true():
            time.sleep(0.5)
            cond.set(50)
            time.sleep(0.5)
            cond.set(100)

        threading.Thread(target = set_true).start()

        # When condition gets set to 50 this should not be released but it
        # should when it gets set to 100
        cond.wait(100)
        self.assertEqual(cond.get(), 100)

