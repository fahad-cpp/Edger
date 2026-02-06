# Edger

**Edger** is a small Windows utility written in C++ that automates searches in Microsoft Edge, it goes through all of your accounts and searches the search list provided in `searchList.txt` for all of the accounts.

The purpose of it is to automate earning Edge Rewards.


## Requirements

* Windows 10/11
* Microsoft Edge installed
* A C++ compiler compatible with the project (gcc recommended)


## Build

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

## Usage

first modify the `searchList.txt` to add searches that you want to search. 

after executing build.bat , you will be able to see a Edger.lnk shortcut , double click on it to run
