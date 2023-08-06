#include <cstdint>
#include <iostream>
#include <algorithm>

#include <cuda_runtime.h>
#include <device_launch_parameters.h>
using namespace std;
__global__ void countValidCombinations(int* ans) {
    int i = blockIdx.x * blockDim.x + threadIdx.x + 1;
    int j = blockIdx.y * blockDim.y + threadIdx.y + 1;

    if (i <= 22 && j <= 22) {
        if (24 - i - j > 0) {
            if (i != j && j != 24 - i - j && i != 24 - i - j) {
                atomicAdd(ans, 1);
            }
        }
    }
}
int main() {
    int ans = 0;
    int* d_ans;

    cudaError_t cudaStatus;

    // 分配设备内存
    cudaStatus = cudaMalloc((void**)&d_ans, sizeof(int));
    if (cudaStatus != cudaSuccess) {
        cerr << "cudaMalloc failed!" << endl;
        return 1;
    }

    // 将主机数据拷贝到设备
    cudaStatus = cudaMemcpy(d_ans, &ans, sizeof(int), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        cerr << "cudaMemcpy failed!" << endl;
        cudaFree(d_ans);
        return 1;
    }

    // 定义CUDA线程块和网格大小
    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks((22 + threadsPerBlock.x - 1) / threadsPerBlock.x,
                   (22 + threadsPerBlock.y - 1) / threadsPerBlock.y);

    // 调用CUDA核函数
    countValidCombinations<<<numBlocks, threadsPerBlock>>>(d_ans);

    // 将设备数据拷贝回主机
    cudaStatus = cudaMemcpy(&ans, d_ans, sizeof(int), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        cerr << "cudaMemcpy failed!" << endl;
        cudaFree(d_ans);
        return 1;
    }

    cout << ans << endl;

    // 释放设备内存
    cudaFree(d_ans);

    return 0;
}