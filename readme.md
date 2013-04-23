zCraft
======

A C++ generative game engine.
Copyright 2010-2013 (c) Marc Gilleron

The project is in an early stage of development, so many things can change
on every new commit. I try to ensure that each version between pushes can
be used without too much bugs or quirks.

Note : the generative part is basically a polygon-based voxel engine (zcraft/ package), 
but it may change in the future.
It is built on top of an engine (engine/ package) that can be used for any game.

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

- GUI (WIP)
- Frustum culling
- OpenGL 3.x (easier switching, at least)
- AABB physics
- Faster voxel archive save format
- Voxel sprites
- And many little things in the code : see TODO comments
- mapgen optimization

Downloads
=========

Nothing "playable" at the moment, but you can test the demos.

Infinite scary cave-canyon test (Windows only) :
https://dl.dropbox.com/u/60408088/INFO/zCraft/2012-12-29-zcraft-map-test.zip

Compiling
=========

Compiler settings :
- C++11, compiles fine with GCC 4.7.2 (I use MinGW on Windows)

Dependencies :
- SFML 2 RC (I recompiled it for the last MinGW)
- OpenGL 2.1 (I should switch to 3 one day)
- Glu
- Glew (I recompiled it for MinGW)

Folder structure
================

The project is divided in several main parts :

- zENG, namespace zn::, folder engine/

This is a set of generic tools I wrote for making games,
and may be used for other projects than zCraft.
It is heavily based on SFML, but some parts are independent.

- zENGui, namespace zn::ui::, folder engine/ui/

This is a generic gui that doesn't depend on anything, except for "very" basic
files such as Vector2, Rect and Color. It is currently developped as part of the
project. All you have to do to use it is to provide your renderer and input.
Note : some renderers and inputs are already programmed.

- zCraft, namespace zcraft::, folder zcraft/

This is the voxel engine, based on zENG.

- Experimental, namespace experimental::

experimental undocumented stuff based on the other packages.
its contents may be future features or tests. I added this to the repo to have a
cloud copy of it (I don't trust my HD) and to ease sharing.

