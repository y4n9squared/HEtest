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

cc_test(
    name = "circuit-handler-test",
    srcs = [
        "circuit-message-handler_test.cc",
    ],
    deps = [
        ":test-harness-lib",
    ],
    linkopts = [
        "-lboost_unit_test_framework",
        "-lboost_system"
    ],
)

cc_test(
    name = "key-handler-test",
    srcs = [
        "key-message-handler_test.cc",
    ],
    deps = [
        ":test-harness-lib",
    ],
    linkopts = [
        "-lboost_unit_test_framework",
        "-lboost_system"
    ],
)

cc_test(
    name = "stream-util-test",
    srcs = [
        "stream-util_test.cc",
    ],
    deps = [
        ":test-harness-lib",
    ],
    linkopts = [
        "-lboost_unit_test_framework",
        "-lboost_system"
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
    linkopts = [
        "-lboost_system",
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
