cmake_minimum_required(VERSION 3.14)

project(minimal
    VERSION 1.0.0
    DESCRIPTION "Failure with Emscripten 3.1.9"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(
    minimal
    src/minimal.cpp
)

target_compile_options(
    minimal PUBLIC -g -s USE_PTHREADS=1 
)

include(FetchContent)
FetchContent_Declare(
  h5wasm
  URL https://github.com/usnistgov/libhdf5-wasm/releases/download/v0.1.1/libhdf5-1_12_1-wasm.tar.gz
  URL_HASH SHA256=e9bb11d89c4f26fa79b9cf1dab6159640c7b184ebf00dc97b098cd4f6de49bfe  
)
FetchContent_MakeAvailable(h5wasm)

target_link_libraries(
    minimal
    hdf5-wasm-cpp
)

set_target_properties(minimal PROPERTIES 
    OUTPUT_NAME minimal
    LINK_FLAGS "--bind -g2 -sSAFE_HEAP=1 -sINITIAL_MEMORY=100MB -s MODULARIZE=1 -s EXPORT_NAME=loadTest -s EXPORT_ES6 -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=4" 
)

# Getting Node to be happy with ES6.
add_custom_command(TARGET minimal POST_BUILD
    COMMAND cat ../preamble.js minimal.js > tmp.js
    COMMAND mv tmp.js minimal.js
    COMMAND cat ../preamble.js minimal.worker.js > tmp.js
    COMMAND mv tmp.js minimal.worker.js
    COMMENT "Adding ES6 preamble for Node"
)
