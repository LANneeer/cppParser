cmake_minimum_required(VERSION 3.23)
project(final)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIRS})
include_directories(/usr/local/include /usr/local/opt/curl/include)

add_executable(final main.cpp)

target_link_libraries(final ${CURL_LIBRARIES})

link_directories(/usr/local/lib /usr/local/opt/curl/lib)
