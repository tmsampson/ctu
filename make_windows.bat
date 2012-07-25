@echo off

:: Create and move to intermediate build directory
mkdir build\intermediate
cd build\intermediate

:: Generate Visual Studio solution
cmake ../../src
IF NOT %ERRORLEVEL%==0 GOTO finish

:: Build ctu using msbuild
msbuild ctu.sln

:: Return to original directory
:finish
cd ../../