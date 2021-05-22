# Ueli
CPU/GPU driven ecosystem for computing DNN and CNN

## Build
Use Win-GenProjects.bat in "scripts" folder to genetate default Visual Studio 2019 solution

If you are using older version of MS Visual Studio, you need to change Win-GenProjects.bat script:

```lua  
pushd ..\
call ThirdParty\premake\bin\premake5.exe vs2019
PAUSE
```
Possible builds vs2005-2019