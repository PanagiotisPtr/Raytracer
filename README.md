# Raytracer Project
My 3rd year dissertation project. A raytracer in C++ for photorealistic renders. (Work in progress)

Here is an example render at it's current state (it's a dog!)
![an rendered image of a dog](https://raw.githubusercontent.com/PanagiotisPtr/Raytracer/main/renders/dog.png)

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

