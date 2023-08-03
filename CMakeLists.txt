cmake_minimum_required(VERSION 3.15)
project(MoviesTest CXX)

# Compiler features
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Dependencies
find_package(httplib REQUIRED)
find_package(RapidJSON REQUIRED)

# Build dependencies
if(DEFINED ENABLE_BUILD_DEPS)
    find_package(GTest REQUIRED)
endif()

# Server executable
set(EXECUTABLE_NAME MoviesTestServer)
add_executable(${EXECUTABLE_NAME} 
    source/main.cpp
    source/movies/get/data/repository.cpp
    source/movies/get/logic/usecase.cpp
    source/movies/get/presentation/controller.cpp
    source/theaters/get/data/repository.cpp
    source/theaters/get/logic/usecase.cpp
    source/theaters/get/presentation/controller.cpp
    source/seats/getAvailable/data/repository.cpp
    source/seats/getAvailable/logic/usecase.cpp
    source/seats/getAvailable/presentation/controller.cpp
    source/seats/book/data/repository.cpp
    source/seats/book/logic/usecase.cpp
    source/seats/book/presentation/controller.cpp
    source/common/data/movie.cpp
    source/common/data/seat.cpp
    source/common/data/session.cpp
    source/common/data/theater.cpp
    source/seats/common/data/find_session.cpp
    source/common/presentation/error_handler.cpp
)
target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_17)
target_link_libraries(
    ${EXECUTABLE_NAME}
    httplib::httplib
    rapidjson
)
target_include_directories(${EXECUTABLE_NAME} PRIVATE 
    source
)

# Tests executable
if(DEFINED ENABLE_BUILD_DEPS)
    set(TEST_EXECUTABLE_NAME MoviesTestTests)
    add_executable(${TEST_EXECUTABLE_NAME} 
        source/movies/get/data/tests.cpp
        source/theaters/get/data/tests.cpp
        source/theaters/get/data/repository.cpp
        source/common/data/movie.cpp
        source/common/data/seat.cpp
        source/common/data/session.cpp
        source/common/data/theater.cpp
        source/movies/get/data/repository.cpp
        source/seats/common/data/find_session.cpp
        source/seats/common/data/tests.cpp
        source/seats/getAvailable/data/repository.cpp
        source/seats/getAvailable/data/tests.cpp
        source/seats/book/data/repository.cpp
        source/seats/book/logic/usecase.cpp
        source/seats/book/data/tests.cpp
        source/seats/book/logic/tests.cpp
    )
    target_compile_features(${TEST_EXECUTABLE_NAME} PRIVATE cxx_std_17)

    target_link_libraries(
        ${TEST_EXECUTABLE_NAME}
        GTest::gtest
        GTest::gmock
        GTest::gtest_main
    )
endif()
