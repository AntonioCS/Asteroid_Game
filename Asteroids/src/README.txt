Asteroid game built with SDL2:

Volodymyr 
Requirements to compile in VS 2017 after “git clone”

1.    Download SDL2 development libraries for Visual C++ (http://libsdl.org/download-2.0.php)
2.    Download SDL_image 2.0 dev libs for VC++ (https://www.libsdl.org/projects/SDL_image/)
3.    Download SDL_ttf 2.0 dev libs for VC++ (https://www.libsdl.org/projects/SDL_ttf/)
4.    Add “your path\include” folders for these 3 dev libs to Additional Include Directories in C/C++/General
5.    Add “your path\lib\x64” folders for these 3 dev libs to Additional Library Directories in Linker/General
6.    Copy all dll files from three “\lib\x64” directories to your project dir (\Asteroid_Game\Asteroids). Has to be 9 dll files total.
7.    Add `$(ProjectDir)data`, `$(ProjectDir)_Interfaces`, `$(ProjectDir)headers` to VC++ Directories/Include directories
8.    Change `std::string font` variable in line 7 in set_up.hpp to your path to `/Asteroids/data/Vector_Battle.ttf` font (edited) 
Thanks Volodymyr

Things still to do (in no particular order):
1. add sound
2. review program layout
3. add restart new game
4. varying draw line thicknesses
