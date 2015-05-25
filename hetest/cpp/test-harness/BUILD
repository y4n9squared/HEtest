cc_library(
    name = "test-harness-lib",
    srcs = [
        "circuit-message-handler.cc",
        "circuit-message-handler.h",
        "key-message-handler.cc",
        "key-message-handler.h",
        "input-message-handler.cc",
        "input-message-handler.h",
        "stream-util.cc",
        "stream-util.h",
        "test-script.cc",
    ],
    hdrs = [
        "test-script.h",
    ],
    deps = [
        "//common:common",
    ],
    copts = [
        "-std=c++11",
   ],
)

cc_binary(
    name = "dummy-client",
    srcs = [
        "dummy-client.cc",
    ],
    deps = [
        "//common:common",
    ],
)

cc_binary(
    name = "test-harness",
    srcs = [
        "test-harness-main.cc",
    ],
    deps = [
        ":test-harness-lib",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
        "-lboost_program_options",
        "-lboost_system",
        "-lboost_iostreams"
    ],
)
