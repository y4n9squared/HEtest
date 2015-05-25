cc_library(
    name = "baseline",
    srcs = ["baseline.cc"],
    hdrs = [
        "baseline.h",
        "circuit-parser.h",
        "lex-global.h",
        "flex-def.h",
        "lemon-def.h",
    ],
    deps = ["//common:common"],
    visibility = [
        "//baseline/ibm:__pkg__",
        "//baseline/stealth:__pkg__",
    ],
)
