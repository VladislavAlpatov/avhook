cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(WIN32_LEAN_AND_MEAN)
message(STATUS "Direct3D 9 SDK path: '$ENV{DXSDK_DIR}'")


link_directories("$ENV{DXSDK_DIR}Lib/x86")
include_directories("$ENV{DXSDK_DIR}Include")

project(avhook)

add_library(avhook MODULE src/main.cpp)
add_subdirectory(src)


find_package(nlohmann_json CONFIG REQUIRED)
find_package(minhook CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(freetype CONFIG REQUIRED)

target_link_libraries(avhook PRIVATE freetype)
target_link_libraries(avhook PRIVATE fmt::fmt-header-only)
target_link_libraries(avhook PRIVATE minhook::minhook)
target_link_libraries(avhook PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(avhook PRIVATE d3dx9)
target_link_libraries(avhook PRIVATE d3d9)

