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
        for (int w = 0; w < nworkers; ++w) {
            workers.emplace_back([]() -> void {});
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
