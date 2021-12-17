cmake_minimum_required(VERSION 3.0.0)
project(filter_app VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/device.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
