# VFS

Implementation of a virtual file system. Aimed more as an exercice than an usable project.

## Getting Started

As a cmake based project, compilation is trivial

```bash
mkdir build
cd build
cmake ..
make
```

### Optionnal requirement

* The documentation can be built with [doxygen](http://www.stack.nl/~dimitri/doxygen/) (>=1.8.3)
* The test suite can be built with [google test](https://github.com/google/googletest)

#### On Ubuntu

```bash
$ sudo apt-get install doxygen libgtest-dev
```

#### On archlinux
```bash
$ sudo pacman -Sy doxygen gtest
```

## Running the tests

Simply build the test suite and launch it.

```bash
$ ./test_vfs
```

You can also launch the test witouth the slow one with :
```bash
$ ./test_vfs --gtest_filter=-"*slow" # to pass slow tests
```

## Built With

* [SHA1](https://github.com/vog/sha1) - Checksum algorithm used
* [cmake](https://cmake.org/) - Build system

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details


