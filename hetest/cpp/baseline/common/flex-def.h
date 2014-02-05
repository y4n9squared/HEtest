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
// Description:        Method declarations and type definitions
//                     for instantiating a flex scanner using the
//                     auto-generated sources stealth-scanner.yy.h
//                     and stealth-scanner.yy.cpp.
//
// Modifications:
// Date          Name           Modification
// ----          ----           ------------
// 17 Aug 2012   yang           Original Version
//*****************************************************************

#ifndef CPP_BASELINE_TA2_CIRCUIT_PARSER_FLEX_DEF_H_
#define CPP_BASELINE_TA2_CIRCUIT_PARSER_FLEX_DEF_H_

// These are declared in flex's auto-generated header stealth-scanner.yy.h 
// and defined in stealth-scanner.yy.cpp. Depending on the build configuration, 
// these files will be created in different subdirectories. Any class that 
// needs to instantiate a flex scanner should include this file, rather than 
// including stealth-scanner.yy.h directly.

typedef void* yyscan_t;

int yylex_init(yyscan_t*);

YYSTYPE yyget_extra(yyscan_t scanner);

int yylex_init_extra(YYSTYPE, yyscan_t*);

int yylex(yyscan_t);

int yylex_destroy(yyscan_t);

struct yy_buffer_state;

typedef struct yy_buffer_state* YY_BUFFER_STATE;

YY_BUFFER_STATE yy_scan_string(const char*, yyscan_t);

void yy_delete_buffer(YY_BUFFER_STATE, yyscan_t);

#endif
