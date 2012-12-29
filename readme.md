zCraft
======

A C++ Minecraft-looking game engine.
Copyright 2010-2012 (c) Marc Gilleron

The project is in an early stage of development, so many things can change
on every new commit. I try to ensure that each version between pushes can
be used without too much bugs or quirks.

Yes, that seems to be another Minecraft clone. Actually, I like to develop such
a thing, and learning some advanced OpenGL. I have some different ideas for the future,
but currently, YES, it appears to be another clone.
Feel free to like the idea or not :-°

![Screenshot](http://zylannprods.fr/games/zcraft/screenshots/2012-12-26-fog-test.png)

Current main features
=====================

- Simple map generators using 2D or 3D perlin noise
- World save format based on 16*16*16 block files
- Built-in 2D top-down world cartographer
- 3D free-flight viewer supporting viewing ranges up to 13*16 nodes without
	dropping under 60fps (on a 2009 laptop, didn't tested over that limit).

Early planned features
================

- Textures
- AABB physics
- World edition
- Basic lighting
- Better save format
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

Libraries :
- SFML 2 (I recompiled it for the last MinGW)
- OpenGL
- Glu
- Glew (I recompiled it for MinGW)

