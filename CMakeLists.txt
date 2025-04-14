cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MultiThreadedUniqueNumberExtractor)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add a flag for enabling pthreads (required for multithreading)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Add the executable
add_executable(MultiThreadedUniqueNumbers main.cpp)

# Link the Threads library
target_link_libraries(MultiThreadedUniqueNumbers PRIVATE Threads::Threads)

# Optionally, you can enable debugging for your build
# set(CMAKE_BUILD_TYPE Debug)
