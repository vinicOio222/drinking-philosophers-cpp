@echo off
REM Build script for the Drinking Philosophers project (Windows version)
setlocal enabledelayedexpansion

echo Creating build directory...
if not exist build mkdir build

cd build

echo Building project...
cmake ..
if errorlevel 1 (
    echo Build failed!
    cd ..
    exit /b 1
)

cmake --build . --config Debug
if errorlevel 1 (
    echo Build failed!
    cd ..
    exit /b 1
)

echo Copying test case files...
copy ..\src\cases\case1.txt . >nul
copy ..\src\cases\case2.txt . >nul
copy ..\src\cases\case3.txt . >nul

echo Running the application...
Debug\drinking-philosophers-cpp.exe
if errorlevel 1 (
    echo Application failed!
    cd ..
    exit /b 1
)

echo Copying results to project root...
if exist results.txt (
    copy results.txt ..\results.txt >nul
    echo Results copied to ..\results.txt
) else (
    echo Warning: results.txt not found
)

cd ..

echo Build and run completed successfully!
pause
