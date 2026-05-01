@echo off
set "BUILD_DIR=build"

:: Check if the build directory exists
if exist "%BUILD_DIR%" (
    echo [INFO] Build directory found. Compiling...
    cmake --build "%BUILD_DIR%"
) else (
    echo [INFO] Creating build directory and configuring...
    mkdir "%BUILD_DIR%"
    cmake -S . -B "%BUILD_DIR%"
    cmake --build "%BUILD_DIR%"
)

pause