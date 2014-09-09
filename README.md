gpgpu
=====

The repository contains the GPGPU examples for the corresponding lessons at BME.
See http://cg.iit.bme.hu/portal/node/311

# Compile and run

First, you need to install the libraries needed. For example, on Ubuntu Trusty:

```
sudo apt-get install cmake build-essential libglu1-mesa-dev libglew-dev freeglut3-dev libdevil-dev
```

Then, you can create a build environment, and then compile with

```
mkdir build
cd build
cmake ../src
make
```

If you want to generate an Eclipse project, you can add `-G "Eclipse CDT4 - Unix Makefiles"`
option to CMake.

You can run the executables compiled (for example, to try lab1, run `./lab1_cg_opengl/lab1`).
See CMake files for executable names.
