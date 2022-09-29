project(42-webserv-neo)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

#add_executable(tests)

#target_link_libraries(
#        tests
#        GTest::gtest_main
#)

include(GoogleTest)
#gtest_discover_tests(tests)
