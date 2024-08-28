project(
    'image',
    ['c', 'cpp'],
    default_options: [
        'c_std=c99',
        'cpp_std=c++20',
        'default_library=both'
    ]
)

# Project include directories.
include_directories = include_directories(
    'include'
)

# Project sources.
sources = files(
    'src/image-decoder.cpp',
    'src/image-encoder.cpp',
    'src/image-encoder-png.c'
)

# STB dependency.
stb_include_directories = include_directories('vendors/stb')
stb_sources = files('vendors/stb/stb_image.cpp')
stb_dep = declare_dependency(
    include_directories: stb_include_directories,
    sources: stb_sources
)

# PNG library dependency.
png_dep = dependency('libpng')

# Package all dependencies together.
dependencies = [
    stb_dep,
    png_dep
]

# Build the library.
image_lib = library(
    'image',
    include_directories: include_directories,
    sources: sources,
    dependencies: dependencies
)

# Exposing as a single dependency in order to use this project as a subproject.
image_dep = declare_dependency(
    include_directories: include_directories,
    link_with: image_lib
)
