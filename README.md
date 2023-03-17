# Wohoo an error 🙌
Have you ever been sad after seeing a flood of error messages? Here comes the solution!

This little program will put a hand selected emoji in front of every message printed to
`stderr`.

## Build and install
1) `mkdir build ; cd build`
2) `cmake -DCMAKE_BUILD_TYPE=RELEASE ..`
3) `sudo make install`

This will build a shared library that gets automatically loaded by the dynamic linker
(probably `ld`). To let `ld` know what to load, the script `register_for_preloading`
will put the library's path into `/etc/ld.so.preload`.
