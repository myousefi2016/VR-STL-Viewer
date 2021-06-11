# VR-STL-Viewer

This code creates a [STL (3D triangular mesh)](https://en.wikipedia.org/wiki/STL_(file_format)) in virtual reality environment. Furthermore, there are pure C++ built-in features that are able to find non-manifold edges, duplicate triangles, and flipped normals in your 3D triangular mesh. Note that you need to use STL format file that is written in **ASCII** format (Binary STL is not supported in this current version). The dependencies that are needed to build this code are:
* CMake >=3.8.
* C++ compiler such as GCC, CLang, Visual C++, etc. (Note that this code is currently tested on a machine with Windows 10 and Visual Studio 2019 installed in it).
* OpenVR SDK.
* VTK built with OpenVR enabled.
* Qt >=6
* SteamVR

This code is tested on a machine that has Windows 10 with Visual Studio 2019 and SteamVR installed that is connected to a HTC Vive VR headset. If you encountered any problem or issue, please open an issue in this repository. If you use this piece of code in your work, please give proper citation and attribution to this repository.
