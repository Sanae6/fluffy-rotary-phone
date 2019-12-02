# Fluffy Rotary Phone
A work in progress game engine.
Built in C++ and uses Lua for scripting.
It's nowhere near ready for use anywhere, as you'd expect when it says work in progress.
## Running
To run the engine make sure you have the proper packages installed. Here's the command I use to install all of the vcpkg ports:
```
vcpkg install sdl2-image sdl2 lua
```
I always use the x64-windows triplet by running the command with the `--triplet x64-windows` flag added.
## To Do
* Audio 
  * **Playing short sounds (asap)**
  * Getting currently playing sounds
  * Sound categories to manage
  * Stopping sounds based on name (sound id string) or categories (ex: seperate music and sfx categories)
* Controller support
* Window management
  * Movement and resize events and functions
  * Hiding and reshowing the window
* Keyboard constants (that's gonna be fun 🙃)
* Mouse support
* Anything useful that I think of
* Anything suggested in an issue at any point