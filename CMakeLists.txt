cmake_minimum_required(VERSION 3.0.0)
project(QRCode VERSION 0.1.0)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(test)
endif()


find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

include_directories(src lib/qrcode/cpp)

add_executable(QRCode src/main.cpp
    lib/qrcode/cpp/QrCode.hpp
    lib/qrcode/cpp/QrCode.cpp)
target_link_libraries( QRCode ${OpenCV_LIBS} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
