find_package(GTest QUIET)

if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0)
    FetchContent_MakeAvailable(googletest)
endif()

add_executable(matrix_tests test_matrix.cpp)
target_link_libraries(matrix_tests PRIVATE matrix GTest::gtest_main)
target_compile_options(matrix_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)

include(GoogleTest)
gtest_discover_tests(matrix_tests)