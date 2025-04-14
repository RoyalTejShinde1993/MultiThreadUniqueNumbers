# MultiThreadUniqueNumbers

This application reads a large file of integers and uses multiple threads to find all unique numbers. Each thread processes a portion of the file independently and contributes to a global set of unique values.

## Build Instructions

### Requirements
- C++17
- CMake >= 3.10

## Output Console
@RoyalTejShinde1993 ➜ /workspaces/MultiThreadUniqueNumbers/build (main) $ /workspaces/MultiThreadUniqueNumbers/build/MultiThreadedUniqueNumbers

Generating large_input.txt using shuf...

File generated successfully.

Output written to: unique_output.txt

Total unique numbers: 1000000

Time taken: 3.87576 seconds

@RoyalTejShinde1993 ➜ /workspaces/MultiThreadUniqueNumbers/build (main) $ 

### Build Steps

```bash
mkdir build
cd build
cmake ..
make
