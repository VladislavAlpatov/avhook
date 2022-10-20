cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(WIN32_LEAN_AND_MEAN)
add_compile_definitions(CLOUD_SUPPORT)
link_directories("C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86")
include_directories("C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include")

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

