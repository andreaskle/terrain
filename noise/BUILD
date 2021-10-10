load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "noise",
    srcs = ["perlin_noise.cpp", "fractal_noise.cpp"],
    hdrs = ["perlin_noise.h", "fractal_noise.h"],
    deps = [
        "@glm//:lib",
    ],
    visibility = ["//visibility:public"],
)
