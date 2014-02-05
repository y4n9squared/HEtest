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
#  Description:        IBM TA2 addition gate class 
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  8 Nov 2012    SY             Original Version
# *****************************************************************

import ibm_gate_two_inps as igti

class IBMAddGate(igti.IBMGateTwoInps):
    """
    This class represents a multiplication gate.
    """
    def __init__(self, displayname, input1, input2, circuit):
        """Initializes the gate"""
        D = max(input1.get_depth(), input2.get_depth()) + .1
        igti.IBMGateTwoInps.__init__(self, displayname, D, input1, input2,
                                     circuit)

    def get_func_name(self):
        """Returns the name of the function which this gate evaluates."""
        return "LADD"
