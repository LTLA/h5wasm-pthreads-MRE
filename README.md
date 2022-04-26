# Minimal example for HDF5 + Pthreads failure

... even though I'm not actually using HDF5 in any parallel regions.

1. Install and activate the latest Emscripten (3.1.9).
2. Run `./build.sh` to build the minimal example.
3. Run `./run.sh` to run through 100 iterations of the test code.

This will usually give errors like:

```
RuntimeError: Aborted(segmentation fault)
    at abort (file:///Users/luna/Programming/js/h5-mre/build/minimal.js:1506:10)
    at segfault (file:///Users/luna/Programming/js/h5-mre/build/minimal.js:924:2)
    at SAFE_HEAP_LOAD_i32_1_U_1 (<anonymous>:wasm-function[605]:0x10071)
    at _emscripten_thread_sync_code (<anonymous>:wasm-function[226]:0x51ea)
    at _emscripten_yield (<anonymous>:wasm-function[241]:0x5a52)
    at emscripten_futex_wait (<anonymous>:wasm-function[227]:0x52cd)
    at __timedwait_cp (<anonymous>:wasm-function[284]:0x7291)
    at __timedwait (<anonymous>:wasm-function[285]:0x72f8)
    at __pthread_mutex_timedlock (<anonymous>:wasm-function[310]:0x7d74)
    at __pthread_mutex_lock (<anonymous>:wasm-function[308]:0x7c62)
```

Observations:

- Failure rate is very low but reproducible; around 1 per 200 runs.
- Doesn't fail with 3.1.8 (tested 600 runs).
