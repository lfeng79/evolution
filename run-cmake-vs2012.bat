mkdir build-win64-vs2012
cd build-win64-vs2012
cmake -G "Visual Studio 11 Win64" ..
cd ..
mkdir build-win32-vs2012
cd build-win32-vs2012
cmake -G "Visual Studio 11" ..
cd ..
pause