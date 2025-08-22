cmake_minimum_required(VERSION 3.22)

if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "Build universal binary" FORCE)
endif()

project(Juce8WebViewProject VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(libs/juce)
add_subdirectory(plugin)