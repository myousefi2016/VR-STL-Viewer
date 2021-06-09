# CMakeList.txt : CMake project for VR-STL-Viewer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package(VTK REQUIRED)

include_directories(${VTK_USE_FILE})

# Add source to this project's executable.
add_executable (VR-STL-Viewer "VR-STL-Viewer.cpp" "VR-STL-Viewer.h")

target_link_libraries(VR-STL-Viewer ${VTK_LIBRARIES})

# TODO: Add tests and install targets if needed.
