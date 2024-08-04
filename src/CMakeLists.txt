cmake_minimum_required(VERSION 3.16)

# Set the project name and language
project(MySFMLApp LANGUAGES CXX)

# Add the executable from main.cpp
add_executable(MySFMLApp main.cpp)

# Find SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Link SFML libraries
target_link_libraries(MySFMLApp PRIVATE sfml-graphics sfml-window sfml-system)

# Optionally, add include directories if needed
# target_include_directories(MySFMLApp PRIVATE ${CMAKE_SOURCE_DIR}/include)