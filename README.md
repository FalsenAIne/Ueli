# Ueli
CPU/GPU driven ecosystem for computing DNN and CNN

## Build
Project requiers python 3.9 with debug libraries installed on your computer.

Use Win-GenProjects.bat in "scripts" folder to genetate default Visual Studio 2019 solution

If you are using older version of MS Visual Studio, you need to change Win-GenProjects.bat script:

```lua  
pushd ..\
call ThirdParty\premake\bin\premake5.exe vs2019
PAUSE
```
Possible builds vs2005-2019

## Structure
Workspace consist of three projects
1. Ueli - cpp shared library with prototypes of mathematical concepts needed for neural network computing
2. Test - cpp console application, made for testing Ueli's code
3. PythonModule - cpp shared library, that includes bindings and is ready to build python module (*.pyd)

## Getting Started
1. Open solution (MS VS2019 is prefered)
2. Make sure configuration is switched to <b>"Release"</b> mode
3. Right-click <b>"PythonModule"</b> project in solution explorer and select <b>"Build"</b>
4. Python binaries are saved in <b>"modules"</b> folder
5. Test binaries calling 
```lua
main.py
```
6. Import module to your python script and enjoy coding!