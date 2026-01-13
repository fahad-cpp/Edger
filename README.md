# Edger

**Edger** is a small Windows utility written in C++ that automates performing searches in Microsoft Edge. It was created to simulate search activity.


## Requirements

* Windows 10/11
* Microsoft Edge installed
* A C++ compiler compatible with the project (MSVC / Visual Studio recommended).
* Administrator privileges may be required for simulated input on some systems.


## Build

To build from source on Windows, open a Command Prompt in the repository root and run:
```batch
mkdir build
cd build

cmake ..
cmake --build .
```
OR
```batch
build.bat
```

## Usage

add list of search prompts in searchlist.txt file
and run the compiled executable:

```batch
bin\Edger.exe
```