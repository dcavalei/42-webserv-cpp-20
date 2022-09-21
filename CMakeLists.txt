cmake_minimum_required(VERSION 3.23)
project(42_webserv_neo)

set(CMAKE_CXX_STANDARD 20)


add_compile_options(-Wall -Wextra -Werror)
add_compile_options(-DDEBUG)

add_executable(42_webserv_neo src/main.cpp src/app/serverApp/serverApp.cpp src/app/serverApp/serverApp.h src/app/configFactory/configFactory.h include/log/log.h src/app/configFactory/cliOptions/cliOptions.cpp src/app/configFactory/cliOptions/cliOptions.h)

target_include_directories(42_webserv_neo PRIVATE src include)
