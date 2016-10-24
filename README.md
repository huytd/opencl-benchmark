# OpenCL Performance Test

This is a simple test to compare the performance between CPU and GPU compuation.

There are two program `cpu.c` and `gpu.c`, both of them will calculate the summary of numbers from `0` to `100 million`. In the end, the program will display the elapsed time.

## How to run

First, you need to compile the programs. This method only works on Apple platform (macOS) for now.

Type the following command to your terminal:

```
make
```

When the compiling finished, you will have 2 binary files: `cpu` and `gpu`.

Run test on CPU:

```
./cpu
```

Run test on GPU:

```
./gpu
```

## What's your test result?

I ran the test on an iMac Late 2015, which has:

```
CPU: 1.6 GHz Intel Core i5
GPU: 1535 MB Intel HD Graphics 6000
```

The runtime result is:

```
CPU: 0.315500ms
GPU: 0.000862ms
```
