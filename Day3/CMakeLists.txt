cmake_minimum_required(VERSION 3.20.0)
project(day3 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

set(INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/powerBanks.txt")

add_executable(day3 main.cpp)

add_custom_command(
    TARGET day3 
    POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy
    "${INPUT_FILE}"
    "$<TARGET_FILE_DIR:day3>/powerBanks.txt"
    COMMENT "Copying powerBanks.txt to the executable directory for debugging"
)