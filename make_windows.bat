@echo off
SET CTU_ROOT_DIR=%CD%
SET CTU_BUILD_DIR=%CTU_ROOT_DIR%\build
SET CTU_INTERMEDIATE_DIR=%CTU_BUILD_DIR%\intermediate
SET CTU_TEST_RESOURCES_DIR=%CTU_ROOT_DIR%\src\ctutest\ctutest_resources

:: Create and move to intermediate build directory
mkdir "%CTU_INTERMEDIATE_DIR%"
cd "%CTU_INTERMEDIATE_DIR%"

:: Generate Visual Studio solution
cmake "%CTU_ROOT_DIR%\src"
IF NOT %ERRORLEVEL%==0 GOTO finish

:: Build ctu using msbuild
msbuild ctu.sln /verbosity:quiet /p:Configuration=Release
IF NOT %ERRORLEVEL%==0 GOTO finish

:: Run unit tests
::cls
echo =====================================================
echo = R U N N I N G = U N I T = T E S T S
echo =====================================================
cd "%CTU_BUILD_DIR%"
xcopy /Y /E /I /Q "%CTU_TEST_RESOURCES_DIR%" "%CTU_BUILD_DIR%\ctutest_resources"
call ctutest
rd /s /q "%CTU_BUILD_DIR%\ctutest_resources"

:: Return to original directory
:finish
cd "%CTU_ROOT_DIR%"