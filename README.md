# Raytracer Project
My 3rd year dissertation project. A raytracer in C++ for photorealistic renders.

Here is an example render at it's current state (it's a dog!)
![an rendered image of a dog](https://raw.githubusercontent.com/PanagiotisPtr/Raytracer/main/renders/dog.png)

And here is the cover image that was used in my dissertation
![an rendered image of a dog](https://raw.githubusercontent.com/PanagiotisPtr/Raytracer/main/renders/cover.png)

## About the project
This project includes the ray tracer program. This is the main part of my dissertation and the program can be used to generate images. Be default, running the raytracer with no arguments will produced the cover photo. Alternatively, you can pass in either a scene file or an instruction file (reference the manual - manual/manual.pdf).

Another part of this project is the scene builder. This lives in its own repository (https://github.com/PanagiotisPtr/3D-Scene-Builder) and is an application that uses OpenGL that allows you to easily set up 3D scenes. Because it uses OpenGL, it only runs on Windows (and possibly linux if you build from sources). You can get the latest binaries of these project on https://github.com/PanagiotisPtr/3D-Scene-Builder/releases/tag/1.0

## How to run the code

### Requirements
You will need
  - A C++ compiler
  - cmake 3.19 or newer
  - lcov (to generate the test coverage reports)
  - gcov (to generate the test coverage reports - usually comes with your C++ compiler)
  - git

Most of those tools come standard (other than cmake 3.19 and lcov) on most unix machines.
For linux you can look up the config.yml file which sets up a linux environment.

### Building and running the code
Building the code is very easy thanks to the ```build.sh``` and ```build_prod.sh``` scripts.
Simply run
```bash
> ./build_prod.sh
> ./raytracer.sh
```

if you want to generate the test coverage reports you will need to build in debug mode using ```build.sh```
```bash
> ./build.sh
> ./generate_coverage.sh
```

### Building on windows
For a windows build, it is recommended that you generate a Visual Studio project and then compile and edit the code from there. To do that you can use CMake on windows, select the main project directory and choose to create a Visual Studio project (this should be the default option). After that, in the build folder, you will find a solution file for the project and everything else you need.