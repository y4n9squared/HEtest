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
#  Description:        Simple wrapper, in case we want to switch
#                      the RNG
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  11 Nov 2011   omd            Original Version
#  27 Sept 2021  jch            Set to stdlib random
#  05 Def  2012  sy             Added gauss and sample, changed seed
# *****************************************************************

import numpy.random
import random

def randint(low, high):
    return numpy.random.randint(low, high+1)

def choice(seq): 
    if not seq:
        raise IndexError
    else:
        x = randint(0, len(seq)-1)
        return seq[x]

shuffle = numpy.random.shuffle

def seed(seed = None):
    numpy.random.seed(seed)
    random.seed(seed)
    
bytes = numpy.random.bytes
gauss = random.gauss
getrandbits = random.getrandbits
sample = random.sample
