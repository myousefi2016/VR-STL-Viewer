# CMakeList.txt : CMake project for VR-STL-Viewer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_AUTOMOC ON)

find_package(VTK REQUIRED)

find_package(Qt6 REQUIRED)

include_directories(${VTK_USE_FILE} ${Qt6_INCLUDES})

FILE(GLOB SOURCES "*.cpp" "*.cc" "*.c" "*.h")

# Add source to this project's executable.
add_executable (${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES} ${Qt6_LIBRARIES})

# TODO: Add tests and install targets if needed.
