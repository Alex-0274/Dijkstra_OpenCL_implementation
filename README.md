# Implementation of Dijkstra's algorithm using C and OpenCL

This project demonstrates in wich cases GPU is better then CPU. For that purposes I used diffrent Dijkstra's algorithm implementations.

## Required

1. clang and clang++ compiler
2. cmake
3. OpenCL
4. bash
5. Linux

## How to build this project

1. Download it

``` bash
git clone ...
```

2. Move to project directory

For example:
``` bash
cd ~/.../Dijkstra_OpenCL_implementation
```

3. Build it

``` bash
cmake -S src -B build
```

## How to run some tests

Please note that the tests may require significant disk space. To optimize performance, they will be generated locally on your device.

All temporary files created during testing will be stored in the system's shared memory directory: /dev/shm/AR_CL_Project_TMP_directory. This ensures faster I/O operations and automatic cleanup after system reboots.

Testing is organized into groups for better clarity. Each group is defined by two parameters:

    1.Number of tests in the group
    2.Number of vertices in each test case

An example of an iteraction:

``` bash
./tests/test_system.sh 10 100 30 10000 50 100000 20 1000000 2 10000000
```
