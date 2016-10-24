CC=gcc

SRC_GPU=gpu.c
SRC_CPU=cpu.c
OUT_GPU=gpu
OUT_CPU=cpu

all: clean gpu cpu

gpu:
	$(CC) $(SRC_GPU) -o $(OUT_GPU) -framework opencl

cpu:
	$(CC) $(SRC_CPU) -o $(OUT_CPU)

clean:
	rm -f $(OUT_GPU) $(OUT_CPU)

