# Matrix Calculator — Lab 3, variant 28
C++17 library for matrix creation, destruction, addition, multiplication,
printing, initialization from an array, transpose and zero-matrix detection.
Errors: std::invalid_argument for bad input, std::bad_alloc for allocation failures.
Free every owning Matrix once using free_matrix; do not use it afterwards.

## Build and run
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
    cmake --build build --parallel
    ./build/matrix_calculator
    ctest --test-dir build --verbose
    valgrind --leak-check=full --error-exitcode=1 ./build/tests/matrix_tests
    doxygen Doxyfile

## Tests and example
Normal operations, 1x1, incompatible dimensions, null input, empty free,
transpose twice, zero matrix, tolerance boundary, invalid tolerance and NaN.
A=[1,2;3,4], B=[5,6;7,8]: A+B=[6,8;10,12], A*B=[19,22;43,50].
Variant 28: [0,0.0001;-0.0001,0] is zero for tolerance 0.001 but not 0.00001.
Dependencies: CMake, C++17, Google Test, Doxygen, Graphviz, Valgrind, Docker.