cmake_minimum_required(VERSION 2.8.9)
project(LAPACK_BandedSym)
find_package(LAPACK REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options timer)

add_executable(LAPACK_BandedSym main.cpp LAPACK_bandedsym_matrix_gen.cpp)
target_link_libraries(LAPACK_BandedSym ${LAPACK_LIBRARIES} Boost::program_options Boost::timer)