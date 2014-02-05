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
#  Description:        unit tests for RandomInt 
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  11 Nov 2011   omd            Original Version
# *****************************************************************

import spar_random
import unittest
import time


# TODO: This should really test that this works with numpy and without by
# forcing the import of numpy to fail but I can't figure out how to cause the
# import to fail.
class RandomIntTest(unittest.TestCase):

    def setUp(self):
        self.seed = int(time.time())
        self.seed_msg = "Random seed used for this test: %s" % self.seed
        self.longMessage = True
        spar_random.seed(self.seed)
    
    def test_correct(self):
        """This tests that the randint function does indeed generate uniformly
        distributed random numbers."""
        observed = {x: 0 for x in xrange(2, 13)}
        # Generate 1000 random numbers
        for i in xrange(10000):
            num = spar_random.randint(2, 12)
            observed[num] += 1

        # Make sure that each number was observed. If things are roughly
        # uniformly distribuited each number should have been observed roughly
        # 1000 times.
        for n in xrange(2, 13):
            self.assertGreater(observed[num], 800, self.seed_msg)
            self.assertLess(observed[num], 1200, self.seed_msg)

    def test_choice(self):
        """ 
        This tests that the choice() function is roughly correct.
        """
        seq = [1,2,3]
        observed = {}
        for i in seq:
            observed[i] = 0
        for i in xrange(1000):
            x = spar_random.choice(seq)
            observed[x] += 1
    
        for i in seq:
            self.assertGreater(observed[i], 250, self.seed_msg)
            self.assertLess(observed[i], 400, self.seed_msg)
        


if __name__ == "__main__":
    unittest.main()
