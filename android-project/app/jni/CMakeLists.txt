cmake_minimum_required(VERSION 3.10)

project(ChordNarashiAndroid)

# Set the root of the project
set(CHORD_NARASHI_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../..")

# Use vcpkg if needed (though it should be passed via command line)
# find_package(SDL3 CONFIG REQUIRED)

# Include the root project
add_subdirectory("${CHORD_NARASHI_ROOT}" "${CMAKE_CURRENT_BINARY_DIR}/root")
