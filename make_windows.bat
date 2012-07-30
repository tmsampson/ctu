@echo off

:: Create and move to intermediate build directory
mkdir build\intermediate
cd build\intermediate

:: Generate Visual Studio solution
cmake ../../src
IF NOT %ERRORLEVEL%==0 GOTO finish

:: Build ctu using msbuild
msbuild /verbosity:quiet ctu.sln
IF NOT %ERRORLEVEL%==0 GOTO finish

:: Run unit tests
cls
echo =====================================================
echo = R U N N I N G = U N I T = T E S T S
echo =====================================================
cd ../
mkdir unit_test_resources
call ctutest
rd /s /q unit_test_resources

:: Return to original directory
:finish
cd ../