# NES (Nintendo Entertainment System) Emulator
An NES emulator using C++ and using olcPixelGameEngine for rendering.

<img src="https://github.com/kmnthecoder/waveNES/blob/master/demo/mario.gif" width="800" height="509">

<img src="https://github.com/kmnthecoder/waveNES/blob/master/demo/dk.gif" width="800" height="509">

<img src="https://github.com/kmnthecoder/waveNES/blob/master/demo/nestest.gif" width="800" height="509">

Only mapper zero has been implemented, and no sound has been implemented either. Thus, only a limited amount of games can run on this.

# How to run
You can drag and drop an NES ROM onto the program, OR you can use command line arguments to run

Drag and drop:

<img src="https://github.com/kmnthecoder/waveNES/blob/master/demo/drag_n_drop.gif" width="800" height="509">

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
To build, you will need the olcPixelGameEngine.h from OneLoneCoder on GitHub.

The makefile I used is included in the repository. I compiled with MinGW-w64 on Windows 10.

# Lessons learned / Final thoughts
This project was undertaken as a next step in emulation programming, after finishing a CHIP-8 emulator. The jump up from CHIP-8 emulator to an NES emulator was quite a challenging one.

In addition to learning more about how certain system components interact with each other, I've learned more about systems programming. Compared to a CHIP-8 emulator, every aspect was taken a step above in terms of complexity. I've learned that every system has it's own quirks, and every system is designed a certain way, and thus, must be programmed for in a certain way as well. This project could not have been possible without javidx9, and I greatly encourage everyone to check out his work on YouTube and GitHub.

The way the original NES designers worked with the limited hardware they had at the time is astonishing. Using tricks to conserve memory, and to reuse assets were very clever. Considering the time period of the 1980s in which the NES was developed in, one should not underestimate the pioneers who came before us.
