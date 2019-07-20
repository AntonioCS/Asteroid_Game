# Asteroid_Game
Reproduction of the classic 1979 Atari Asteroid Arcade Game in C++ and SDL2

Requirements to compile in VS 2017 after “git clone”

1.    Download SDL2 development libraries for Visual C++ (http://libsdl.org/download-2.0.php)
2.    Download SDL_image 2.0 dev libs for VC++ (https://www.libsdl.org/projects/SDL_image/)
3.    Download SDL_ttf 2.0 dev libs for VC++ (https://www.libsdl.org/projects/SDL_ttf/)
4.    Download #include SDL_mixer 2.0 dev libs for VC++ (https://www.libsdl.org/projects/SDL_mixer/)
5.    Add “your path\include” folders for these 4 dev libs to Additional Include Directories in C/C++/General
6.    Add “your path\lib\x64” folders for these 4 dev libs to Additional Library Directories in Linker/General
7.    Copy all dll files from three “\lib\x64” directories to your project dir (\Asteroid_Game\Asteroids). 
8.    Add `$(ProjectDir)data`, `$(ProjectDir)_Interfaces`, `$(ProjectDir)headers`, `$(ProjectDir)sounds` to VC++ Directories/Include directories
9.    Change `std::string font` variable in line 7 in set_up.hpp to your path to `/Asteroids/data/Vector_Battle.ttf` font (edited) 
Thanks Volodymyr

Things still to do (in no particular order):
1. review program layout
2. varying draw line thicknesses
3. Add high score record list, display and user input
4. Increase beat frequency as game continues
5. automatic window and game scaling
