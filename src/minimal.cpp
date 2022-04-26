#include <emscripten/bind.h>
#include <vector>
#include <thread>
#include <cmath>
#include <string>
#include "H5Cpp.h"

void foobar() {
    int nworkers = 4;

    {
        std::vector<std::thread> workers;
        workers.reserve(nworkers);

        std::atomic<bool> ready(false);
        for (int w = 0; w < nworkers; ++w) {
            workers.emplace_back([&]() -> void {
                ready.store(true);
            });

            // No wait until C++20, so we'll do it the stupid way.
            while (!ready.load()) {
                std::this_thread::sleep_for(std::chrono::microseconds(10));
            }
            ready.store(false);
        }

        for (auto& wrk : workers) {
            wrk.join();
        }
    }

    return;
}

// Force HDF5 to get linked in.
void create_hdf5_file() {
    H5::H5File handle;
    return;
}

EMSCRIPTEN_BINDINGS(foobar) {
   emscripten::function("foobar", &foobar);
}
