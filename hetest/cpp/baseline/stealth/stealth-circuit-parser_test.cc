//*****************************************************************
// Copyright (c) 2013 Massachusetts Institute of Technology
//
// Developed exclusively at US Government expense under US Air Force contract
// FA8721-05-C-002. The rights of the United States Government to use, modify,
// reproduce, release, perform, display or disclose this computer software and
// computer software documentation in whole or in part, in any manner and for
// any purpose whatsoever, and to have or authorize others to do so, are
// Unrestricted and Unlimited.
//
// Licensed for use under the BSD License as described in the BSD-LICENSE.txt
// file in the root directory of this release.
//
// Project:            SPAR
// Authors:            Yang
// Description:        Unit tests for Parser
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 20 Sep 2012  yang            Original Version
//*****************************************************************

#define BOOST_TEST_MODULE ParserTest

#include "stealth-circuit-parser.h"
#include "circuit.h"
#include "common/test-init.h"

using namespace std;

// Check that a circuit object returns the correct value given its circuit and
// input strings. Create a simple 2-input one-gate circuit and verify its logic
// table.
BOOST_AUTO_TEST_CASE(ParseOrGate) {

  string circuit_str = "W=2output_gate: OR(W0, W1)";

  StealthCircuitParser p;
  auto_ptr<Circuit> c = p.ParseCircuit(circuit_str);
  BOOST_CHECK_EQUAL(c->Evaluate("[0,0]", false), 0);
  BOOST_CHECK_EQUAL(c->Evaluate("[0,1]", true), 1);
  BOOST_CHECK_EQUAL(c->Evaluate("[1,0]", false), 1);
  BOOST_CHECK_EQUAL(c->Evaluate("[1,1]", true), 1);
}

BOOST_AUTO_TEST_CASE(ParseAndGate) {

  string circuit_str = "W=2\
                    output_gate: AND(W0, W1)";

  StealthCircuitParser p;
  auto_ptr<Circuit> c = p.ParseCircuit(circuit_str);
  BOOST_CHECK_EQUAL(c->Evaluate("[0,0]", false), 0);
  BOOST_CHECK_EQUAL(c->Evaluate("[0,1]", true), 0);
  BOOST_CHECK_EQUAL(c->Evaluate("[1,0]", false), 0);
  BOOST_CHECK_EQUAL(c->Evaluate("[1,1]", true), 1);
}

// Slightly more complicated gate with more levels.
BOOST_AUTO_TEST_CASE(ParseLargerGate) {
  string circuit_str = "W=2\
                        G0: AND(W0, W1)\
                        G1: OR(W0, W1)\
                        output_gate: XOR(N(G0), G1, W0)";
  StealthCircuitParser p;
  auto_ptr<Circuit> c = p.ParseCircuit(circuit_str);
  BOOST_CHECK_EQUAL(c->Evaluate("[0,1]", true), 0);
  BOOST_CHECK_EQUAL(c->Evaluate("[1,0]", true), 1);
}

BOOST_AUTO_TEST_CASE(ParseLargestGate) {
  string circuit_str = "W=2 \
                        G34: XOR(W0, N(W1)) \
                        L \
                        G32: AND(W1, G34) \
                        output_gate: OR(W0, N(G34), G32)";
  StealthCircuitParser p;
  auto_ptr<Circuit> c = p.ParseCircuit(circuit_str);
  BOOST_CHECK_EQUAL(c->Evaluate("[1,1]", true), 1);
}

