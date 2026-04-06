cmake_minimum_required(VERSION 3.16)
project(port_scanner CXX)

set(CMAKE_CXX_STANDARD 17)

# Use static runtime for compatibility with Boost libraries
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
if(NOT DEFINED CMAKE_CXX_FLAGS_RELEASE)
    set(CMAKE_CXX_FLAGS_RELEASE "/MT /O2")
endif()

add_executable(port_scanner
    main.cpp
    src/PortScanner.cpp
)

target_include_directories(port_scanner PRIVATE
    "C:/boost/boost_1_90_0"
)

target_link_directories(port_scanner PRIVATE
    "C:/boost/boost_1_90_0/stage/lib"
)

target_link_libraries(port_scanner PRIVATE
    libboost_program_options-vc142-mt-s-x64-1_90
    libboost_thread-vc142-mt-s-x64-1_90
    libboost_chrono-vc142-mt-s-x64-1_90
    libboost_atomic-vc142-mt-s-x64-1_90
)