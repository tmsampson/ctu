@echo off

:: Create and move to intermediate build directory
mkdir build\intermediate
cd build\intermediate

:: Generate Visual Studio solution
cmake ../../src
IF NOT %ERRORLEVEL%==0 GOTO finish

:: Build ctu using msbuild
msbuild ctu.sln
IF NOT %ERRORLEVEL%==0 GOTO finish

:: Run unit tests
cls
echo =====================================================
echo = R U N N I N G = U N I T = T E S T S
echo =====================================================
call ..\ctutest

:: Return to original directory
:finish
cd ../../
