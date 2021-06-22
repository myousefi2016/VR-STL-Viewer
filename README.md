# VR-STL-Viewer

This code creates a [STL (3D triangular mesh)](https://en.wikipedia.org/wiki/STL_(file_format)) in virtual reality environment. Furthermore, there are pure C++ built-in features that are able to find non-manifold edges, duplicate triangles, and flipped normals in your 3D triangular mesh. Note that you need to use STL format file that is written in **ASCII** and **Binary** format (Now binary STL is supported in this current version). The dependencies that are needed to build this code are:
* CMake >=3.8.
* C++ compiler such as GCC, CLang, Visual C++, etc. (Note that this code is currently tested on a machine with Windows 10 and Visual Studio 2019 installed in it).
* OpenVR SDK.
* VTK built with OpenVR enabled.
* Qt >=6
* SteamVR

This code is tested on a machine that has Windows 10 with Visual Studio 2019 and SteamVR installed that is connected to a HTC Vive VR headset. If you encountered any problem or issue, please open an issue in this repository. If you use this piece of code in your work, please give proper citation and attribution to this repository.

## Using binary pre-built package

If you don't want to build this code, you can use the binary pre-built install package for Windows 10 that is provided in [**Release**](https://github.com/myousefi2016/VR-STL-Viewer/releases/download/1.0/VR.STL.Viewer.msi) section of this repository. Note that you need to install Qt >=6 and put the correct path in your environment variables. For example put `C:\Qt\6.2.0\msvc2019_64\bin` into your environment variable and then you should be able to use the software.

## Benchmark

In order to observe how the mesh cleaner to remove the duplicate triangles, identify the flipped normals and non-manifold edges would be scaled by increasing the number of triangles in the 3D mesh, a benchmark for a 3D mesh of a turbine blade is done here, where its topology remained the same but the number of meshes are decimated from 1M to 100K and the runtime of 3D mesh cleaner part is measured in second and plotted here:

![benchmark](https://user-images.githubusercontent.com/22246708/122986708-c5e5cd80-d36d-11eb-9fde-6f92165a34c1.png)

We see that there is an exponential scaling of the runtime vs. the number of triangles in the 3D mesh due to increased number of collisions in the hash function defined in `utilities.h` for `triangle` and `edge` classes.

## VR Viewer in *action*

https://user-images.githubusercontent.com/22246708/121732338-1e8caf00-cac0-11eb-9557-74c5592f2c67.mp4


https://user-images.githubusercontent.com/22246708/121741446-8cd76e80-cacc-11eb-8021-e1d0befbab0d.mp4

