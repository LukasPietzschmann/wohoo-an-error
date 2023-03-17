# Wohoo an error 🙌
Have you ever been sad after seeing a flood of error messages? Here comes the solution!

This little program will put a hand selected emoji in front of every message printed to
`stderr`.

<p align="center">
	<img src="https://user-images.githubusercontent.com/49213919/225991307-8745ef18-c67d-4360-bbd4-93e8cb24c6bd.png" height="300" />
</p>

## Options
You can set the environment variable `WOHOO` to `FALSE` in order to deactivate the
code. This will only apply to applications started after you set the variable.

## Build and install
1) `mkdir build ; cd build`
2) `cmake -DCMAKE_BUILD_TYPE=RELEASE ..`
3) `sudo make install`

This will build a shared library that gets automatically loaded by the dynamic linker
(probably `ld`). To let `ld` know what to load, the script `register_for_preloading`
will put the library's path into `/etc/ld.so.preload`.

## Disclaimer
You should be careful what you put into `ld.so.preload`. You can seriously mess up your
system by automatically loading garbage. And while I haven't had any issued with this
little project, I cannot make any guarantee that this will be the case for your system,
too.
