cmake_minimum_required(VERSION 3.0)

project(pss_test
    LANGUAGES C
)

add_subdirectory(pss)

add_executable(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/main.c")
target_link_libraries(${PROJECT_NAME} PRIVATE pss::pss)