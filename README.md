# libsquish
<img align="left" src="https://i.imgur.com/nRgZRya.png" width=50%>

The squish library (primarily known by libsquish) is an open source DXT/S3TC compression library written in C++ that is commonly used with OpenGL and DirectX for the lossy compression of RGBA textures.

[![Dev Builds](https://github.com/oblivioncth/libsquish/actions/workflows/build-project.yml/badge.svg?branch=dev)](https://github.com/oblivioncth/libsquish/actions/workflows/build-project.yml)

**Features:**
 - Supports the DXT1, DXT3 and DXT5 formats.
 - Optimized for both SSE and Altivec SIMD instruction sets.
 - Builds on multiple platforms (x86 and PPC tested).
 - Very simple interface (single header squish.h).
 - Conforms to the S3TC and DXT standard
 - Easy creation of compressed textures for OpenGL, DirectX, and other renderers
 - Reentrant API for parallelization purposes
 - OpenMP support



## Modern CMake Fork
libsquish was originally developed by Simon Brown (si@sjbrown.co.uk), and is currently maintained by 
Stefan Roettger (snroettg@gmail.com) on [SourceForge](https://sourceforge.net/projects/libsquish/).

This fork features a reorganized source structure and completely rewritten CMake scripts that employ "Modern CMake" practices.

However, this does come at the cost of requiring CMake 3.23 or greater.

**Differences Summary:**

 - In-built package configuration file(s) that obviates the need for an external Find-module
 - Full compatibility with CMake's `FetchContent` mechanism
 - Use of alias targets and export names that allow for seamless consumption of targets regardless of whether the library was acquired via `FetchContent`/`add_subdirectory()` or `find_package()`
 - All outward facing facets of the library's CMake implementation are pre-fixed with `libsquish` instead of simply `squish`. This avoids confusion and collision issues with the Squish GUI testing framework (i.e. the built-in FindSquish.cmake module)
 - The public header is now in a project specific sub-directory. Incude via `#include <squish/squish.h>` instead of just `#include <squish.h>`
 - Install components of the package are automatically set to `EXCLUDE_FROM_ALL` if libsquish is not the top-level project in order to prevent unwanted pollution of its install prefix. The components can still be installed explicitly
 - Each target is neatly contained in its own subdirectory
 - Use of more target specific property modifiers where available (e.g. `target_compile_definitions()` and `target_compile_options()` instead of `add_definitions()`)
 - Propegation of required compiler options (e.g. `-fopenmp`) to consumers when building libsquish statically 
 - Promotion of the color error test application to a proper autotest via CTest
 - Exports for the "extra" PNG and Generator demo applications
 - CMake target for building the documentation
 - CI/CD via GitHub Actions for generating online documentation, builds, and releases


See the *Packaging* and *Building From Source* sections of the [documentation](https://oblivioncth.github.io/libsquish/) for a detailed overview of the various CMake options, targets, install components, etc.

Support for the other build systems (e.g. qmake, standalone GNU make) has been removed due to the source structure changes. They may be reworked and re-added at a later time.

The actual library code has remained essentially untouched, aside from a few minor tweaks to account for the build script and source directory changes.

Although unlikely given libsquish's maturity, if functional changes occur within the upstream library they will be synchronized here.

## Documentation:
Detailed documentation of this library, facilitated by Doxygen, is available at: https://oblivioncth.github.io/libsquish/

## Getting Started
Either grab the latest [release](https://github.com/oblivioncth/libsquish/releases/) or [build the library from source](https://oblivioncth.github.io/libsquish/index.html#autotoc_md6), and import using CMake.

Building from source is recommended as this library can easily be integrated as a dependency into your project using CMake's FetchContent. An example of this is demonstrated in the documentation.

Finally, the [Minimal Example](https://oblivioncth.github.io/libsquish/index.html#autotoc_md5), gives a basic overview of how to use the public interface.

### Summary

 - C++98
 - CMake 3.23.0

### Dependencies
- [OBCMake](https://github.com/oblivioncth/OBCmake) (build script support, fetched automatically)
- [Doxygen](https://www.doxygen.nl/)  (for documentation)
 
## Pre-built Releases/Artifacts

Releases and some workflows currently provide builds of libsquish in various combinations of platforms and compilers. View the repository [Actions](https://github.com/oblivioncth/libsquish/actions) or [Releases](https://github.com/oblivioncth/libsquish/releases) to see examples

## License

The squish library is distributed under the terms and conditions of the MIT
license. This license is specified at the top of each source file and must be
preserved in its entirety.