#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
void CPURun()
{
    printf(" CPU work.\n");
}
__global__ void GPURun()
{
    printf("GPU work.\n");
}

int main()
{
    CPURun();
    GPURun << <1, 1 >> > ();
    cudaDeviceSynchronize();
    return 0;
}