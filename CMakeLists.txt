# We want to at least be running CMake 3.00 on our build systems.
cmake_minimum_required(VERSION 3.00)

# The project name and version.
project(FXLib VERSION "0.1.4")

# Include Package Config for CMake.
find_package(PkgConfig REQUIRED)

# Set the C++ standard that the library will use (C++17).
set(CMAKE_CXX_STANDARD 17)

# Set the C standard that the library will use (C11).
set(CMAKE_C_STANDARD 11)

# Get the current build time in YYYY-MM-DD formatting in UTC-0 (GMT-1).
string(TIMESTAMP PROJECT_BUILD_DATE "%Y-%m-%d" UTC)

# Integrate CMake with our C/C++ project for versioning and project naming.
configure_file(config.h.in config.h)

# Integrate 3rd party libraries into our project.
pkg_check_modules(JSONCPP jsoncpp)

# Set our variable named "SOURCES" to point to the directory that our C and C++ source files will reside.
set(SOURCES ${PROJECT_SOURCE_DIR}/source)

# Set our variable named "HEADERS" to point to the directory that our C and C++ header files will reside.
set(HEADERS ${SOURCES}/headers)

# Include our build directory since it'll contain our modified config.h file.
include_directories(
   ${PROJECT_BINARY_DIR}
   ${JSONCPP_INCLUDE_DIRS}
   ${HEADERS}
)

# Tell the compiler which source and header files are needed in order to build the library.
set(
   LIBRARY_FILES
   ${SOURCES}/libfx.cc
)

# CMake options that will determine how this library is built.
option(BUILD_SHARED_OBJECT "Build this library as a shared object for external linking." ON)
option(BUILD_STATIC_OBJECT "Build this library as a static object for embedding into another project." ON)
option(BUILD_DEBUG_BINARY  "Build this library as an executable binary for debug purposes." ON)

# If the option to build a shared object is enabled then create a shared library.
if(${BUILD_SHARED_OBJECT})
   add_library(FXLib SHARED ${LIBRARY_FILES})
endif()

# If the option to build a static object is enabled then build a static library.
if(${BUILD_STATIC_OBJECT})
   add_library(FXLib STATIC ${LIBRARY_FILES})
endif()

# If the option to build a debug binary is enabled then create an executable binary for testing purposes.
if(${BUILD_DEBUG_BINARY})
   add_executable(FXLib_debug ${LIBRARY_FILES})
   target_link_libraries(FXLib_debug ${JSONCPP_LIBRARIES})
endif()

# Link the 3rd party libraries we rely upon.
target_link_libraries(FXLib ${JSONCPP_LIBRARIES})