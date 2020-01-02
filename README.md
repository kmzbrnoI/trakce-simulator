# Trakce Simulator library

This repository contains sources of the Trakce library, which could be used as
a replacement of [real
track-control-system](https://github.com/kmzbrnoI/xn-lib-cpp-qt) for
[hJOPserver](https://hjop.kmz-brno.cz/hJOPserver).

This library implements
[Trakce API](https://github.com/kmzbrnoI/xn-lib-cpp-qt/wiki).

## Building & toolkit

This SW was developed in `vim` using `qmake` & `make`. Downloads are available
in *Releases* section. It is suggested to use `clang` as a compiler, because
then you may use `clang-tools` during development process (see below).

### Prerequisities

 * Qt 5
 * Optional: clang build tools (see below)
 * Optional for clang: [Bear](https://github.com/rizsotto/Bear)

### Example: toolchain setup on Debian

```bash
$ apt install qt5-default
$ apt install clang-7 clang-tools-7 clang-tidy-7 clang-format-7
$ apt install bear
```

### Build

Clone this repository:

```
$ git clone https://github.com/kmzbrnoI/xn-lib-cpp-qt
```

And then build:

```
$ mkdir build
$ cd build
$ qmake -spec linux-clang ..
$ bear make
```

## Cross-compiling for Windows

This library could be cross-compiled for Windows `dll` via [MXE](https://mxe.cc/).
Follow [these instructions](https://stackoverflow.com/questions/14170590/building-qt-5-on-linux-for-windows)
for building standalone `dll` file.

You may want to use activation script:

```bash
export PATH="$HOME/...../mxe/usr/bin:$PATH"
~/...../mxe/usr/i686-w64-mingw32.static/qt5/bin/qmake ..
```

## Style checking

```
$ clang-tidy-7 -p build -extra-arg-before=-x -extra-arg-before=c++ -extra-arg=-std=c++14 -header-filter=. *.cpp
$ clang-format-7 *.cpp *.h
```

## Authors

This library was created by:

 * Jan Horacek ([jan.horacek@kmz-brno.cz](mailto:jan.horacek@kmz-brno.cz))

Do not hesitate to contact author in case of any troubles!

## License

This application is released under the [Apache License v2.0
](https://www.apache.org/licenses/LICENSE-2.0).
