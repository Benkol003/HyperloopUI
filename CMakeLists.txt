cmake_minimum_required(VERSION 3.24)

project(HyperloopUI LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/) #places dll's from library dependencies in same folder
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_STATIC_LIBS ON)

#set qt install location here if needed
set (CMAKE_PREFIX_PATH "D:\\Qt\\6.3.1\\msvc2019_64\\")
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/json)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/curl)


set(LIBS
    libcurl
    nlohmann_json::nlohmann_json
    Qt6::Core
    Qt6::Widgets
)

set(SOURCES
${CMAKE_SOURCE_DIR}/src/main.cpp
)

add_executable(main ${SOURCES})
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include/ Qt6::Widgets)
target_link_libraries(main PUBLIC ${LIBS})
set_property(TARGET main PROPERTY AUTOMOC ON) #needed for qt Q_OBJECT macros