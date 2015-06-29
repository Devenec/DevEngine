## DevEngine

A 3D game development framework  
Version 0.0.1


### About

DevEngine is written in C++. It is aimed to be a powerful cross-platform game
development framework, which hopefully evolves into a complete game engine.
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

- Proper memory management and allocators
- OpenGL 3.x support
- Multithreading support


### Supported Platforms

- Windows (tested only on Windows 7)


### Third Party Source Code Included

- [libpng] 1.6.17
- [OpenGL and WGL API] header files
- [zlib] 1.2.8


### Building

Visual Studio 2013 and [Visual C++ Compiler November 2013 CTP] is required.


### Copyright & License

Copyright 2015 Eetu 'Devenec' Oinasmaa  
Licensed under GNU General Public License.

The third party source code may be licensed under different licenses, as
described in LICENCE-3RD-PARTY.txt


[libpng]: http://www.libpng.org/pub/png/libpng.html
[OpenGL and WGL API]: https://www.opengl.org/registry/#headers
[zlib]: http://www.zlib.net/
[Visual C++ Compiler November 2013 CTP]: http://www.microsoft.com/en-us/download/details.aspx?id=41151
