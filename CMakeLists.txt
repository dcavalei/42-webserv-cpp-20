cmake_minimum_required(VERSION 3.16)
project(42_webserv_neo)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -Wpedantic)

add_subdirectory(third-parties)
add_subdirectory(include)

option(BUILD_TESTS "" ON)
option(BUILD_EXAMPLES "" ON)

if (BUILD_TESTS)
    message(STATUS "Building tests...")
    add_subdirectory(tests)
endif ()

if (BUILD_EXAMPLES)
    message(STATUS "Building examples...")
    add_subdirectory(examples)
endif ()

add_executable(42_webserv_neo src/main.cpp src/app/serverApp/serverApp.cpp src/app/serverApp/serverApp.h src/app/configFactory/configFactory.h src/app/configFactory/cliOptions/cliOptions.cpp src/app/configFactory/cliOptions/cliOptions.h src/app/signalHandler/signalHandler.cpp src/app/signalHandler/signalHandler.h src/app/serverConf/serverConf.cpp src/app/serverConf/serverConf.h src/app/serverConf/server/server.h src/app/serverConf/server/location.h include/http/request.cpp include/http/request.h include/http/http.cpp include/http/http.h src/app/serverConf/server/redirect.h)

target_include_directories(42_webserv_neo PRIVATE src include third-parties)

target_link_libraries(42_webserv_neo yaml-cpp)