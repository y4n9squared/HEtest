
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
#  Description:        Stealth TA2 XOR gate class 
# 
#  Modifications:
#  Date          Name           Modification
#  ----          ----           ------------
#  17 Oct 2012   SY             Original Version
#  08 Nov 2012   SY             Incorporated Oliver's feedback
# *****************************************************************

import stealth_gate as sg
import common.spar_random as sr

class StealthXorGate(sg.StealthGate):
    """
    This class represents a XOR gate. It is a subclass of Gate.

    Simple use:
    # Instantiate the inputs to our XOR gate as follows:
    wire1 = StealthInputWire("wire1", True)
    wire2 = StealthInputWire("wire2", False)
    # Instantiate our XOR gate as follows:
    this_gate = StealthXorGate("this_gate",[wire1,wire2],[False,False])
    # Our XOR gate can be prompted to return its value as follows:
    val = this_gate.evaluate()
    # val will be equal to True.
    """
    def __init__(self, displayname, inputs, negations):
        sg.StealthGate.__init__(self, displayname, inputs, negations)

    def get_func_name(self):
        """Returns the name of the function which this gate evaluates ("OR")."""
        return "XOR"
    
    def _evaluate_based_on_inputs(self):
        """Uses the inputs to compute the output of the XOR gate."""
        return (sum((self._get_value_with_negation(eval_ind)
                     for eval_ind in xrange(self.get_num_inputs()))) % 2 == 1)
        
    def balance(self, desired_output):
        """Changes the negations on the inputs of this gate so that the gate
        yeilds the bit desired_output."""
        assert(desired_output == True or desired_output == False)
        current_eval = self.evaluate()
        # if the gate does not currently evaluate to the desired_output, tweak
        # the negations in such a way as to force it to evaluate to the
        # desired_output. This can be done by flipping a single negation:
        inp_ind = sr.randint(0, self.get_num_inputs() - 1)
        self._negate(inp_ind)
        self._set_value(desired_output)
