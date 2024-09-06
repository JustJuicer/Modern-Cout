cmake_minimum_required(VERSION 3.29.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()  

find_package(Catch2)
if (NOT Catch2_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        Catch2 
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG devel 
    )  
    FetchContent_MakeAvailable(Catch2)
endif()

project(testing)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} Catch2::Catch2WithMain)
add_test(NAME ${PROJECT_NAME}
        COMMAND ${PROJECT_NAME}
)