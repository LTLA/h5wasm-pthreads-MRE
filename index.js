import loadTest from "./build/minimal.js";

// The Emscripten-packaged Node is too old, can't take file URIs: so we strip that out.
const options = { locateFile: (x) => import.meta.url.substring(7) + "/../build/" + x };

loadTest(options).then(module => {
    module.foobar();
    module.PThread.terminateAllThreads();
});


