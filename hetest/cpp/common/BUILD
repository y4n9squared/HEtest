package(default_visibility = ["//visibility:public"])

cc_library(
    name = "common",
    srcs = [
        "statics/ordered-function-registry.h",
        "statics/ordered-function-registry.cc",
        "statics.cc",
        "output-handler.h",
        "output-handler.cc",
        "logging.cc",
        "string-algo.cc",
        "timer.cc",
        "util.cc"
    ],
    hdrs = [
        "statics.h",
        "logging.h",
        "timer.h",
        "util.h",
        "string-algo.h",
    ],
)

cc_test(
    name = "ordered-function-registry-test",
    srcs = ["statics/ordered-function-registry_test.cc"],
    deps = [":common"],
    includes = ["boost_unit_test_framework"],
    linkopts = ["-lboost_unit_test_framework", "-lboost_system"],
)

cc_test(
    name = "timer-test",
    srcs = ["timer_test.cc"],
    deps = [":common"],
    includes = ["boost_unit_test_framework"],
    linkopts = ["-lboost_unit_test_framework", "-lboost_system"],
)

cc_test(
    name = "string-algo-test",
    srcs = ["string-algo_test.cc"],
    deps = [":common"],
    includes = ["boost_unit_test_framework"],
    linkopts = ["-lboost_unit_test_framework", "-lboost_system"],
)

cc_test(
    name = "util-test",
    srcs = ["util_test.cc"],
    deps = [":common"],
    includes = ["boost_unit_test_framework"],
    linkopts = ["-lboost_unit_test_framework", "-lboost_system", "-lboost_iostreams"],
)

cc_test(
    name = "check-test",
    srcs = ["check_test.cc"],
    deps = [":common"],
    includes = ["boost_unit_test_framework"],
    linkopts = ["-lboost_unit_test_framework", "-lboost_system", "-lboost_regex"],
)

cc_test(
    name = "logging-test",
    srcs = ["logging_test.cc"],
    deps = [":common"],
    includes = ["boost_unit_test_framework"],
    linkopts = ["-lboost_unit_test_framework", "-lboost_system"],
)

cc_test(
    name = "topological-iterator-test",
    srcs = ["topological-iterator_test.cc"],
    deps = [":common"],
    includes = ["boost_unit_test_framework"],
    linkopts = ["-lboost_unit_test_framework", "-lboost_system"],
)
