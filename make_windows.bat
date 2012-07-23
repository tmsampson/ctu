:: Windows batch script

:: Create and move to intermediate build directory
mkdir build\intermediate
cd build\intermediate

:: Generate ctu Visual Studio solution
cmake ../../src

:: Build ctu using msbuild
msbuild ctu.sln