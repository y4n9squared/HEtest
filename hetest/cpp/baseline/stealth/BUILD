genrule(
    name = "flex-gen",
    srcs = [
        "stealth-scanner.l",
    ],
    outs = [
        "stealth-scanner.yy.cpp",
        "stealth-scanner.yy.h",
    ],
    cmd = "flex $(SRCS) && mv $$PWD/stealth-scanner.yy.* $(@D)",
)

genrule(
    name = "lemon-gen",
    srcs = [
        "stealth-parser.y",
    ],
    outs = [
        "stealth-parser.cc",
        "stealth-parser.h",
    ],
    cmd = "lemon $(SRCS) && mv /Users/y4n9/repos/hetest/hetest/cpp/baseline/stealth/stealth-parser.c $(location stealth-parser.cc) && mv /Users/y4n9/repos/hetest/hetest/cpp/baseline/stealth/stealth-parser.h $(location stealth-parser.h)",
)

cc_library(
    name = "stealth-baseline",
    srcs = [
        "or.cc",
        "or.h",
        "and.cc",
        "and.h",
        "not.h",
        "xor.cc",
        "xor.h",
        "wire.h",
        "multi-input-gate.cc",
        "multi-input-gate.h",
        "stealth-circuit-parser.cc",
        "stealth-circuit-parser.h",
        "circuit.cc",
        "circuit.h",
        "stealth-baseline.cc",
        "stealth-baseline.h",
        "stealth-parser.cc",
        "stealth-parser.h",
        "stealth-scanner.yy.cpp",
        "stealth-scanner.yy.h",
        "stealth-baseline-main.cc",
    ],
    deps = [
        "//baseline/common:baseline",
    ],
    copts = [
        "-Wno-deprecated-register",
        "-std=c++11",
    ],
    linkopts = ["-lboost_system"],
)
