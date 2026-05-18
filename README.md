# Edger

**Edger** is a small Windows utility written in C++ that automates searches in Microsoft Edge, it goes through all of your accounts and searches the search list provided in `searchList.txt` for all of the accounts.

The purpose of it is to automate earning Edge Rewards.
## Download

Click here -> [Download](https://github.com/fahad-cpp/Edger/releases/download/1.0.0/Win-x64.zip)

## Usage
Download and extract the zip from release

- make sure all your edge profiles have maximized windows (does not work if windows are not maximized)
- searchList.txt contains the searches to perform automatically
- modify searchList.txt and run Edger-x64.exe , that's all :)

## Requirements for compiling

* Windows 10/11 (For Windows.h)
* Microsoft Edge installed
* A C++ compiler compatible with the project (gcc recommended)

## Build

it is recommended to download and use binary from release but if you want to build, <br>
To build from source on Windows, open a Command Prompt in the repository root and run:

```batch
build.bat
```

if somehow the project build fails with build.bat , you can try compiling manually using CMake:

```batch
mkdir build
cd build

cmake .. -DCMAKE_BUILD_TYPE="Release"
cmake --build . --config Release
```
