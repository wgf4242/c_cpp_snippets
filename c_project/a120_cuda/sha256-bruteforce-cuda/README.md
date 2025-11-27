```sh
# 性能分析
$ nsys profile -t cuda --stats=true sha256_cracker_cuda 8a62da7ab7a41006fe47d385621214dcf01d4fd87e45a0de829d449565880dc6
```

## Brute-Force SHA-256 Cracking with CPU and CUDA Implementations

- `sha256_cracker_cpu.c`: Pure C program using OpenSSL’s SHA‑256 to brute‑force passwords on the CPU.
- `sha256_cracker_cuda.cu`: CUDA-based GPU implementation for faster parallel password cracking.

### Compile and Run

**CPU Version**:

```bash
cc sha256_cracker_cpu.c -o sha256_cracker_cpu -lcrypto
./sha256_cracker_cpu <target_hash>
```

**CUDA Version**:

```bash
nvcc sha256_cracker_cuda.cu -o sha256_cracker_cuda
./sha256_cracker_cuda <target_hash>
```
