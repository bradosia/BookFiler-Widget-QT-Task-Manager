# BookFiler Widget w/ QT: Task Manager Widget
This is a QT5 widget that creates a task list to monitor task progress. This widget uses a `sqlite3` backend.

# Build Instructions

## Windows - MinGW-w64
Install MSYS2<BR>
Then, install GCC, cmake, git and dependencies. Confirmed working with Windows 10 as of 11/19/2020.
```shell
pacman -Syu
pacman -S mingw-w64-x86_64-gcc git make mingw-w64-x86_64-cmake
pacman -Rns cmake
# restart MSYS2 so that we use the mingw cmake
pacman -S mingw-w64-x86_64-boost mingw-w64-x86_64-tesseract-ocr
```
Build:
```shell
git clone https://github.com/bradosia/BookFiler-Lib-Sort-Filter-Tree-Widget
cd BookFiler-Module-HTTP
mkdir build
cd build
cmake -G "MSYS Makefiles" ../
make
```

## Linux Ubuntu
Install GCC, cmake, git and dependencies. Confirmed working with Ubuntu 20.04 as of 11/8/2020.
```shell
sudo apt-get update
sudo apt install build-essential gcc-multilib g++-multilib cmake git
sudo apt install libboost-all-dev mingw-w64-x86_64-sqlite3
```
Build:
```shell
git clone https://github.com/bradosia/BookFiler-Lib-Sort-Filter-Tree-Widget
cd BookFiler-Module-HTTP
mkdir build
cd build
cmake ../
make
```

# Developers

[Developer Notes](/dev/readme.md)
