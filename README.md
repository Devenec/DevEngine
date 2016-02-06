## DevEngine

A 3D game development framework  
Version 0.0.2


### About

DevEngine is written in C++. It is aimed to be a powerful cross-platform game
development framework, which will hopefully evolve into a complete game engine.
DevEngine uses OpenGL for rendering.

Please note that DevEngine is heavily a work in progress, and many things will
change in the future. Also the licensing may change in the future.


### Current Features

#### Layered Structure

The framework subsystems are layered in a way that prevents circular
dependencies. This makes subsystem development and testing more independent.

#### Platform Independence

All platform dependent code is located in a single subsystem/layer. Supporting
new platforms and maintaining existing ones is fast and easy.

#### Content Management

Game content (assets) are managed by a central component, which loads all
supported content types via a single method. Also, users can easily add support
for custom content types.


### Upcoming Features

- Proper memory management
- Proper multithreading support


### Supported Platforms

- Linux (tested on Xubuntu 14.04 x64)
- Windows (tested on Windows 7 x64 and Windows 10 x64)


### Building

#### Linux

Clang 3.6 and (GNU) Make 3.81 is required (older versions may also work).

The project depends on the following additional libraries:
- libc++
- libGL(.so)
- libX11
- libXrandr

Call ```make``` in the root directory. See the root makefile for configuration.

#### Windows

Visual Studio 2015 is required.

Open build/devengine.sln and build the solution. libpng and zlib projects are
excluded from "Build Solution" on Debug configuration, and they need to be
built separately. This way, when rebuilding the entire solution, they don't
need to be rebuilt and some time is saved.


### Third Party Source Code Included

- [libpng] 1.6.21
- [GLX, OpenGL and WGL API] header files
- [zlib] 1.2.8


### Copyright & License

Copyright 2015-2016 Eetu 'Devenec' Oinasmaa  
Licensed under GNU General Public License.

The third party source code may be licensed under different licenses, as
described in LICENCE-3RD-PARTY.txt


[libpng]: http://www.libpng.org/pub/png/libpng.html
[GLX, OpenGL and WGL API]: https://www.opengl.org/registry/#headers
[zlib]: http://www.zlib.net/
