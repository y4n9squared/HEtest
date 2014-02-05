
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
#  Description:        IBM TA2 gate superclass 
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  22 Oct 2012   SY             Original Version
# *****************************************************************

import ibm_circuit_object as ico

class IBMGate(ico.IBMCircuitObject):
    """
    This class represents a boolean gate.
    It is an 'abstract' class extended by subclasses, one corresponding to
    each boolean gate type. The class IBMGate is never meant to be instantiated;
    only its subclasses are.
    """
    def __init__(self, displayname, D, level, circuit):
        """Initializes the gate with a display name, depth D, a level,
        and a circuit."""
        ico.IBMCircuitObject.__init__(self, displayname, D, level, circuit)
        
    def get_func_name(self):
        """Returns the name of the function which this gate evaluates.
        This should never be called from the abstract superclass IBMGate."""
        # This method should be overriden in the subclasses.
        assert(False)
