# 这个模板的名字为 cout
# 查找并替换 cout
# 项目结构：
# .
# ├── CMakeLists.txt
# ├── include
# │   └── cout
# │       └── cout.h
# ├── src
# │   └── cout.cpp
# └── Test
#     ├── CMakeLists.txt
#     └── main.cpp

cmake_minimum_required(VERSION 3.29.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()  

project(cout)

file(GLOB LIB_SRC src/*.cpp include/*.h include/cout/*.hpp)

add_library(cout 
                            STATIC 
#                           SHARED
                            ${LIB_SRC}
)
add_library(cout::cout ALIAS cout)
set_target_properties(cout 
    PROPERTIES 
    LANGUAGE CXX
)
include(CMakePackageConfigHelpers)
# set install path:
#SET(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)
target_include_directories(cout PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
# set_target_properties(cout PROPERTIES PUBLIC_HEADER include/cout.hpp)
install(TARGETS cout
    EXPORT cout-targets
    PUBLIC_HEADER DESTINATION include
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
#use this if you want to install cout directory to install-path/include but not single header
# install(DIRECTORY  ${CMAKE_SOURCE_DIR}/include/cout DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/cout.hpp
    DESTINATION include
)
install(EXPORT cout-targets
    NAMESPACE cout::
    FILE cout-config.cmake
    DESTINATION lib/cmake/cout
)

include_directories(${CMAKE_SOURCE_DIR}/include)



enable_testing()
add_subdirectory(test/catch)
add_subdirectory(test/print)
