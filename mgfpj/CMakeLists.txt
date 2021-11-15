# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.18)

# Set the project name
project (mgfpj LANGUAGES CUDA CXX)

find_package(RapidJSON CONFIG REQUIRED)

find_package(CUDAToolkit)

set(CMAKE_CUDA_ARCHITECTURES 52)
set(CMAKE_CUDA_RUNTIME_LIBRARY Static)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/mgfpj.cpp
    src/stdafx.cpp
    src/FpjClass.cpp
    src/FpjClass_Agent.cu
)

# Add an executable with the above sources
add_executable(mgfpj ${SOURCES})

target_compile_features(mgfpj PUBLIC cxx_std_17)

target_link_libraries(mgfpj 
    PRIVATE 
        rapidjson
        CUDA::toolkit 
)

set_target_properties(mgfpj PROPERTIES CUDA_SEPARABLE_COMPILATION  ON)

# Set the directories that should be included in the build command for this target
target_include_directories(mgfpj
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

############################################################
# Install
############################################################
install(TARGETS mgfpj DESTINATION bin)