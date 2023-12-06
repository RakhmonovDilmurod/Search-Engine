cmake_minimum_required(VERSION 3.5)

project(search_engine LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
googletest
URL
https://github.com//google//googletest//archive//609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
include(GoogleTest)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(gtest_disable_pthreads on)

add_subdirectory(nlohmann_json)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(search_engine

    src/main.cpp
    answers.json
    config.json
    requests.json
    include/SearchServer.h
    include/ConvertJSON.h
    include/InvertedIndex.h
    README.md)
target_include_directories(search_engine PUBLIC include)
target_include_directories(search_engine PUBLIC src)
include(GNUInstallDirs)
install(TARGETS search_engine
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(search_engine PRIVATE gtest_main)
gtest_discover_tests(search_engine)
enable_testing()






