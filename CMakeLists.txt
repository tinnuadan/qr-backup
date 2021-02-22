cmake_minimum_required(VERSION 3.0.0)
project(QRCode VERSION 0.1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(test)
endif()

find_library(LIBQRCODEGEN qrcodegencpp)

include_directories(src)

add_executable(QRCode src/main.cpp src/qrcode_wrapper.cpp)

target_link_libraries( QRCode ${LIBQRCODEGEN} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
