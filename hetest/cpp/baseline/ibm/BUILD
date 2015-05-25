genrule(
    name = "flex-gen",
    srcs = [
        "ibm-scanner.l",
    ],
    outs = [
        "ibm-scanner.yy.cpp",
        "ibm-scanner.yy.h",
    ],
    cmd = "flex $(SRCS) && mv $$PWD/ibm-scanner.yy.* $(@D)",
)

genrule(
    name = "lemon-gen",
    srcs = [
        "ibm-parser.y",
    ],
    outs = [
        "ibm-parser.cc",
        "ibm-parser.h",
    ],
    cmd = "lemon $(SRCS) && mv /Users/y4n9/repos/hetest/hetest/cpp/baseline/ibm/ibm-parser.c $(location ibm-parser.cc) && mv /Users/y4n9/repos/hetest/hetest/cpp/baseline/ibm/ibm-parser.h $(location ibm-parser.h)",
)

cc_binary(
    name = "ibm-baseline",
    srcs = [
        "binary-gate.cc",
        "binary-gate.h",
        "unary-gate.cc",
        "unary-gate.h",
        "rotate.cc",
        "rotate.h",
        "ibm-circuit-parser.cc",
        "ibm-circuit-parser.h",
        "circuit.cc",
        "circuit.h",
        "ibm-baseline.cc",
        "ibm-baseline.h",
        "ibm-parser.cc",
        "ibm-parser.h",
        "ibm-scanner.yy.cpp",
        "ibm-scanner.yy.h",
        "ibm-baseline-main.cc",
    ],
    deps = [
        "//baseline/common:baseline",
    ],
    copts = [
        "-Wno-deprecated-register",
    ],
    linkopts = ["-lboost_system"],
)

"""
cc_test(
    name = "ibm-gate-test",
    srcs = ["ibm-gate_test.cc"],
    deps = [":ibm-baseline-lib"],
    includes = ["boost_unit_test_framework"],
    linkopts = ["-lboost_unit_test_framework", "-lboost_system"],
)

cc_test(
    name = "ibm-circuit-parser-test",
    srcs = ["ibm-circuit-parser_test.cc"],
    deps = [":ibm-baseline-lib"],
    includes = ["boost_unit_test_framework"],
    linkopts = ["-lboost_unit_test_framework", "-lboost_system"],
)
"""
