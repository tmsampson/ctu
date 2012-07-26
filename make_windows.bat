@echo off

:: Create and move to intermediate build directory
mkdir build\intermediate
cd build\intermediate

:: Generate Visual Studio solution
cmake ../../src
IF NOT %ERRORLEVEL%==0 GOTO finish

:: Build ctu using msbuild
msbuild ctu.slns

:: Run unit tests
cls
echo #####################################################
echo # R U N N I N G   U N I T   T E S T S
echo #####################################################
call ..\Debug\ctutest

:: Return to original directory
:finish
cd ../../
