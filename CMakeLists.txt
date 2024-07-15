cmake_minimum_required(VERSION 3.10)
project(ImTool)

# Enable compile_commands.json generation
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use the environment variable
set(FTXUI_DIR "$ENV{VENDOR}/ftxui-5.0.0-win64")

# Specify C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the FTXUI header files
include_directories(${FTXUI_DIR}/include)

# Add your executable target
add_executable(bitwise src/main.cpp)

# Link FTXUI libraries
target_link_libraries(bitwise 
    ${FTXUI_DIR}/lib/ftxui-component.lib 
    ${FTXUI_DIR}/lib/ftxui-dom.lib 
    ${FTXUI_DIR}/lib/ftxui-screen.lib
)

# Set output directories based on build type
set_target_properties(bitwise PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug
)

# Specify where to place the compile_commands.json
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Debug")
