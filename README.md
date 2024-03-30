# Jspace for NEO6502
 
This game is a test written entirely in C compatible with both the cc65 compiler and llmv-mos. The graphics are not great, in fact, I'm not capable of creating graphics. However, it's a good scrolling test with tile maps.

Additionally, everyone can create their own levels by changing the graphics contained in the file `graphics.gfx`, and especially customize the tilemaps by modifying the text files (for example`input_level0.txt`). Through the Python program `create_binary_map.py` the binary file is created which the program then loads.

The enemies come in three types:

- One type of enemy that follows the player.
- A ghost enemy type that appears and disappears on the screen according to an array of data.
- A type of enemy that moves step by step randomly.
- Lastly, one that moves with movements present in an array (enemy array). The speeds and numbers of enemies vary from level to level.

Player score is saved at the end of each game, whether won or lost. The top 10 scores are retained. At the start of the game, the player is prompted for their name.

The program compiles with the file `./compile.sh` for the llmv-mos compiler, see the wiki [LLVM-MOS](https://github.com/paulscottrobson/neo6502-firmware/wiki/Using-LLVM-for-MOS) for some information.

The program compiles with the file `./compile_jspace.sh` for the CC65 compiler, see the [examples] (https://github.com/paulscottrobson/neo6502-firmware/tree/main/examples/C) for some information.

There is a significant difference in program speed when using the CC65 compiler, as well as in the size of the executable file. I have not yet verified if everything is due to code optimization by the compilers.

Variables are located in the file global.h.
The variable DELAY_GAME allows modifying the scroll delay, while the variable DELAY_SCREEN adjusts the time non-game screens remain idle before a key press is accepted.
The variable VELOCITY_MISSILE adjusts missile speed.
The delay should be longer when using the emulator compared to hardware.

I know the code is not great, but it's been years since I programmed and I've lost my touch.

To play, you can use both compatible joysticks/gamepads and the keyboard.

The next steps are:

- Manage a configuration file to indicate the number of levels. Currently, there are 7 levels numbered from 0 to 6. This will allow creating as many levels as desired with the desired graphics.
- Support a configuration file for the arrays and speeds of ghost and array type enemies.
