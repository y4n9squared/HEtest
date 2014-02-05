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
#  Description:        TA2 input class test 
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  14 Nov 2012   SY             Original Version
# *****************************************************************

import circuit_input as ci
import unittest

class TestInput(unittest.TestCase):

    def test_display(self):
        """
        Tests the display method in the Input class works as intended.
        """
        elt1 = "element1"
        elt2 = "element2"
        inp = ci.Input([elt1, elt2])
        self.assertEqual("[element1,element2]", str(inp))
        
if __name__ == '__main__':
    stc.unittest.main()
