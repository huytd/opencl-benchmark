#include <stdio.h>
#include <stdlib.h>
#include <OpenCL/opencl.h>
#include <time.h>

#define MAX_SOURCE_SIZE (0x100000)

int main() {
  cl_device_id device_id = NULL;
  cl_context context = NULL;
  cl_command_queue command_queue = NULL;
  cl_mem memobj = NULL;
  cl_program program = NULL;
  cl_kernel kernel = NULL;
  cl_platform_id platform_id = NULL;
  cl_uint ret_num_devices;
  cl_uint ret_num_platforms;
  cl_int ret;

  cl_ulong val[1];

  FILE *fp;
  char fileName[] = "./sum.cl";
  char *source_str;
  size_t source_size;

  fp = fopen(fileName, "r");
  if (!fp) {
    fprintf(stderr, "Failed to load kernel\n");
    exit(1);
  }
  source_str = (char*)malloc(MAX_SOURCE_SIZE);
  source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
  fclose(fp);

  ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
  ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);

  context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

  command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

  memobj = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_mem), NULL, &ret);

  program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);

  ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

  kernel = clCreateKernel(program, "hello", &ret);

  ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&memobj);

  clock_t begin = clock();

  ret = clEnqueueTask(command_queue, kernel, 0, NULL, NULL);

  ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0, sizeof(cl_mem), val, 0, NULL, NULL);

  clock_t end = clock();
  double runtime = (double)(end - begin) / CLOCKS_PER_SEC;

  ret = clFlush(command_queue);
  ret = clFinish(command_queue);
  ret = clReleaseKernel(kernel);
  ret = clReleaseProgram(program);
  ret = clReleaseMemObject(memobj);
  ret = clReleaseCommandQueue(command_queue);
  ret = clReleaseContext(context);

  printf("Result: %llu\n", val[0]);
  printf("Runtime: %lfms\n", runtime);
  
  free(source_str);

  return 0;
}
