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
#  Description:        Timer object 
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  23 May 2012   omd            Original Version
# *****************************************************************

import datetime

class Timer(object):
    def __init__(self):
        self.start_time = None
        self.end_time = None

    def Start(self):
        self.start_time = datetime.datetime.now()

    def Stop(self):
        self.end_time = datetime.datetime.now()

    NUM_MICROS_PER_SECOND = 1000000.0
    def Elapsed(self):
        elapsed = self.end_time - self.start_time
        elapsed_sec = (elapsed.seconds + 
                float(elapsed.microseconds) / self.NUM_MICROS_PER_SECOND)
        return elapsed_sec

