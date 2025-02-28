# This must be the very first line
cmake_minimum_required(VERSION 3.8)

# This must come before project()
set(CMAKE_TOOLCHAIN_FILE "C:/Users/riley/vcpkg/scripts/buildsystems/vcpkg.cmake" 
    CACHE STRING "Vcpkg toolchain file")

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("hftTradingEngine")

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Print vcpkg status for debugging
message(STATUS "Using vcpkg toolchain at: ${CMAKE_TOOLCHAIN_FILE}")

# Explicitly set CURL paths
set(CURL_INCLUDE_DIR "C:/Users/riley/vcpkg/installed/x64-windows/include")
set(CURL_LIBRARY "C:/Users/riley/vcpkg/installed/x64-windows/lib/libcurl.lib")

# Try to find cURL
find_package(CURL REQUIRED)

# Include sub-projects
add_subdirectory("hftTradingEngine")