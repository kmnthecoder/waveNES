# NES (Nintendo Entertainment System) Emulator
An NES emulator using C++ and using olcPixelGameEngine for rendering.

=== // insert gifs here // ===

Only mapper zero has been implemented, and no sound has been implemented either. Thus, only a limited amount of games can run on this.

# How to run
You can drag and drop an NES ROM onto the program, OR you can use command line arguments to run

Drag and drop:
=== // insert picture here // ===

Command Line Format:

    PROGRAM_PATH FILE_PATH
    
Example:

    ./waveNES ./roms/donkey_kong.nes

    
# Keys
Keys are mapped to:

    NES Controller      Your keyboard
          A         =>        A
          B         =>        S
          START     =>        Z
          SELECT    =>        X
          D-PAD     =>        Arrow Keys

# Building
To build, you will need the olcPixelGameEngine.h from OneLoneCoder on github.

The makefile I used is included in the repository. I compiled with MinGW-w64.

# Lessons learned / Final thoughts
This project was undertaken as a next step in emulation programming, after finishing a 
