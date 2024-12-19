[![Build](https://github.com/pbentes/ProjectTemplate/actions/workflows/build.yml/badge.svg)](https://github.com/pbentes/ProjectTemplate/actions/workflows/build.yml)
[![CodeFactor Grade](https://img.shields.io/codefactor/grade/github/pbentes/projecttemplate)](https://www.codefactor.io/repository/github/pbentes/projecttemplate)
![GitHub License](https://img.shields.io/github/license/pbentes/ProjectTemplate)

# C++ Project Starter Template

This is a quick-start project template for C++ projects which utilise a core/app project architecture. There are two included projects - one called core, and one called app. CMake is used to generate project files.

Core builds into a static library and is meant to contain common code intended for use in multiple applications. App builds into an executable and links the Core static library, as well as provides an include path to core's code.

## Getting Started

1) Clone this repository or use the "Use this template" button on GitHub to quickly set up your own repository based on this template
2) App/ and Core/ are the two projects - you can edit the names of these folders and their contents to suit
3) The three included CMake build files are CMakeLists.txt, core/CMakeLists.txt and app/CMakeLists.txt - you can edit these to customise your build configurations, edit the names of your projects and workspace/solution, etc.
4) Create a build folder, cd into it and run `cmake ..` to generate a project

To build the project run the following commands:

```
cmake -S . -B build
cmake --build build
```

## Included

- Some example code (in app/src, core/src and tests/src) to provide a starting point
- An example of how to use CMake to fetch dependencies in the vendor folder
- An example test written using the [GoogleTest](https://google.github.io/googletest/) library
- .gitignore to ignore project files and binaries
- Github Actions to check for build status and run the tests

## License

UNLICENSE (see UNLICENSE.txt for more details)

## Credits

This project template is inspired by TheCherno's [Project Template](https://github.com/TheCherno/ProjectTemplate/tree/master) using Premake5.
