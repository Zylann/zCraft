zCraft
======

A C++ framework for making games.
Copyright 2010-2013 (c) Marc Gilleron

This project is a set of files I use for developping games in C++.
It also features a voxel engine for 3D OpenGL testing and maybe some games.
I regularly copy some parts of this framework when I start a project, and then
backups new stuff to it as reusable components, so I don't have to rewrite stuff.

![Screenshot](http://zylannprods.fr/games/zcraft/screenshots/2013-02-19-crafted-zcraft.png)

Current main features
=====================

Framework :

- Some essentials (Vector2, Vector3, Rect, AABB, Matrix4...)
- Dependence-free generic GUI (windows, buttons, wrapped text, sliders, dragging, skins...)
- OpenGL utility (Vertex/Pixel/Geometry shaders, basic direct-draws, VBO...)
- BMFont implementation
- Template entity-based game structure (Experimental)
- Random stuff (Platform-specific things, math utilities, logging...)

Voxel engine :

- Simple map generators using 2D or 3D perlin noise
- World save format based on N*N*N block files, where N=16 (not efficient, but working)
- Built-in 2D top-down world cartographer
- 3D free-flight viewer supporting viewing ranges up to 13*16 cubes without
	dropping under 60fps (on a 2009 laptop, didn't tested over that limit).

Third-party :

- UTF8 conversion for text internationalization
- Simplex noise

Some planned features
================

Note: depends on which project I currently work on.

- OpenGL 3.x (easier switching, at least)
- More GUI widgets
- Scripting interfaces for AngelScript, Lua and Python
- AABB physics
- Voxel engine: Faster voxel archive save format
- Voxel engine: Frustum culling
- Voxel engine: volumetric sprites
- Voxel engine: mapgen optimization
- And many little things in the code : see TODO comments

Downloads
=========

There is actually nothing "playable", but there is a main() function.
that means you can test some technical demos :)

Infinite scary cave-canyon test (Windows only) :
https://dl.dropbox.com/u/60408088/INFO/zCraft/2012-12-29-zcraft-map-test.zip

Compiling
=========

A few days ago, I switched to CMake. However, I'm new to this build system,
so the CMakeLists.txt may be a bit awkward.
It is recommended to use a separate build/ directory for the building process
(notice it in .gitignore) in which you specify your environnment (paths to libs).
If you can't get it to work, try Code::Blocks or another build system.

Compiler requirements :
- C++11, compiles fine with GCC 4.7.2 or MinGW on Windows.
(MSVC compatibility is not my priority until I really need it)

Dependencies sum for ALL the project :
- SFML 2.0 (GCC 4.7 DW2)
- OpenGL 2.1 (I should switch to 3 one day)
- Glu
- Glew (I recompiled it for MinGW)

Execute
========

The execution directory must be the same as the assets/ folder (i.e repo's root).

Folder structure
================

The project is divided in several main parts :

- zENG, namespace zn::, folder engine/ (also called zCraft Engine)

This is the framework of tools I write for making games,
and may be used for other projects than zCraft.
Multimedia parts are heavily based on SFML, but only when it's really needed
(for example, the core/ folder doesn't depend on anything but config.hpp,
system/osdefines.hpp and the STL).

- zENGui, namespace zn::ui::, folder engine/gui/

This is a generic gui that only depends on the core/ and utf8/ parts of the engine.
It is currently developped as part of the project.
All you have to do to use it is to provide your renderer and input.
Note : some renderers and inputs are already included.

- zCraft, namespace zcraft::, folder zcraft/

This is the voxel engine, based on zENG.

- Tests

experimental undocumented stuff based on the other packages.
its contents may be future features or tests. I added this to the repo to have a
cloud copy of it (I don't trust my HD) and to ease sharing.

