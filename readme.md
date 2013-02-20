zCraft
======

A C++ voxel game engine.
Copyright 2010-2012 (c) Marc Gilleron

The project is in an early stage of development, so many things can change
on every new commit. I try to ensure that each version between pushes can
be used without too much bugs or quirks.

![Screenshot](http://zylannprods.fr/games/zcraft/screenshots/2013-02-19-crafted-zcraft.png)

Current main features
=====================

- Simple map generators using 2D or 3D perlin noise
- World save format based on N*N*N block files, where N=16 (not efficient, but working)
- Built-in 2D top-down world cartographer
- 3D free-flight viewer supporting viewing ranges up to 13*16 cubes without
	dropping under 60fps (on a 2009 laptop, didn't tested over that limit).

Early planned features
================

- Frustum culling
- GUI
- OpenGL 3.x (easier switching, at least)
- AABB physics
- Faster voxel archive save format
- Voxel sprites
- And many little things in the code : see TODO comments

Downloads
=========

Nothing "playable" at the moment, but you can try the test builds.

Infinite scary cave-canyon test (Windows only) :
https://dl.dropbox.com/u/60408088/INFO/zCraft/2012-12-29-zcraft-map-test.zip

Compiling
=========

Compiler settings :
- C++11 norm with GCC 4.7.2 (I use MinGW on Windows)

Dependencies :
- SFML 2 RC (I recompiled it for the last MinGW)
- OpenGL 2.1
- Glu
- Glew (I recompiled it for MinGW)

Folder structure
================

The project is divided in two main parts, where only one depends on the other.

- zENG, namespace engine::

engine/	: Generic code for many things. Doesn't depend on zcraft/.
engine/opengl/ : Everything that is OpenGL-related is here.
engine/bmfont/ : Implementation of a BMFont renderer. Depends on engine/opengl/.
engine/system/ : OS-specific stuff (macros, threading, files...)

experimental/ : experimental undocumented stuff based on engine/.
	its contents may be future features. I added this to the repo to have a
	cloud copy of it (I don't trust my HD) and to ease sharing.

- zCraft, namespace zcraft::

zcraft/ : The voxel engine. It is based on the engine/ package.
zcraft/games/ : Test-purpose games based on zcraft/.
zcraft/cartographer/ : built-in map cartographer
zcraft/mapgen/ : map generators


