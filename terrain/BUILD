load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "terrain",
    srcs = [
        "camera.cpp",
        "camera.h",
        "grid.cpp",
        "grid.h",
        "main.cpp",
        "scene.cpp",
        "scene.h",
        "vertex.h",
    ],
    data = glob(["shaders/*.glsl"]),
    deps = [
        "//interpolation",
        "//noise",
        "//opengl:utils",
        "//third_party/glad",
        "@glfw//:lib",
        "@glm//:lib",
        "@stb//:lib",
    ],
)
