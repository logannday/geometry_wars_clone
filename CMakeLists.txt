cmake_minimum_required(VERSION 3.0)

project(SFMLApp)

# Set C++ standard to C++11 or higher
set(CMAKE_CXX_STANDARD 17)

# Specify the compiler as g++
set(CMAKE_CXX_COMPILER g++)

# Compiler Commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add the -g flag for debugging information
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Find SFML package
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Add your source files
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

# Include directories for headers
include_directories(include)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link SFML libraries to your project
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)

