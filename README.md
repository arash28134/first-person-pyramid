# First Person Pyramid
First Person Pyramid is a 3D demo made possible using GLFW, GLEW and GLM libraries. it uses basic functionalities of GLFW library (and 3D graphics) such as View, Projection and Model matrices; as well as other concepts like window creation and input handling.

![Alt text](preview.gif?raw=true "Preview Gif")
## Installation
To install the demo, either [Build from source](#building-from-source) or download a pre-built binary from [Releases](https://github.com/arash28134/first-person-pyramid/releases) section.
## Building from source
- For building the demo, first make sure you have the dependencies installed by running:
```
./dependencies.sh
```
- Now, run the build script:
```
./build.sh
```
- Alternatively, you can use build script's **--r** flag and have the demo automatically run after build:
```
./build.sh --r
```
- Finally, cd into build directory and run the demo:
```
cd build
./first_person_pyramid
```
- If you get an error related to file's permissions, run:
```
chmod +x first_person_pyramid
```
## Dependencies
All dependencies needed for running the demo can be found in **dependencies.txt** file; which is used by **dependencies.sh**.
## Bindings
Keyboard bindings used in the demo are listed in **bindings.txt** file (keep in mind that the listed bindings aren't set dynamically, and **bindings.txt** is just a reference to bindings used in program's source)
## Current issues
At the moment, we don't have any CMake configurations setup for Windows and Mac.