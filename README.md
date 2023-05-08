# SPACETYPING


## Installing
>**For Linux, please follow [this link](https://www.paulbarrick.com/game-devlopment/game-development-on-linux-using-vscode-sdl2-and-opengl/) to install.**

>**For Window, please follow these steps**

**Step 1:** Install [MinGW && GNU C++](https://www.youtube.com/watch?v=a3ejgWLqelQ)
- If having used any version of MinGW32 before, you can skip this step

**Step 2:** Install SDL 2.0 library
 - You can use raw library in this source code.

## Building

**Step 1:** **Download** and **extract** source code

**Step 2:** Open file **Global.hpp** in folder **include/headers**, change the `PATH_BEGIN` at line **17**

**Step 3:** Open **Command Prompt** (cmd), **direct** to the extracted folder and type command `mingw32-make` (Window) or `make` (Linux)

**Step 4:** Run game by typing command `SpaceTyping`