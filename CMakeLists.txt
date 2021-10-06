cmake_minimum_required(VERSION 3.16)
project(geant4sandpit VERSION 0.1.0)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory("rutherford")

# Special code formatting target
include(cmake/clang-format.cmake)
