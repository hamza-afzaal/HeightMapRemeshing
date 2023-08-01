cmake_minimum_required (VERSION 3.5.1) # Not sure what the minimum is required
project (HeightMapRemeshing CXX C)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Use modern C++
SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

include_directories("${PROJECT_BINARY_DIR}" libs src)

set(glm_DIR "libs/glm/cmake/glm")
find_package(glm REQUIRED)

# include_directories($(GLM_INCLUDE_DIR))

# Add your source files here
file(GLOB sources src/*.c src/*.h src/*.cpp src/*.hpp)

# Create the executable
add_executable(HeightMapRemeshing ${sources})

# Link libraries
target_link_libraries(HeightMapRemeshing PRIVATE glm::glm)