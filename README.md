# Asteroid_Game
Reproduction of the classic 1979 Atari Asteroid Arcade Game in C++ and SDL2

Requirements to compile in VS 2017 after “git clone”

- If you have vcpkg integrated with Visual Studio you should not need to do anything
- If not you have to specify the vcpkg toolchain file in you cmake call, example: cmake -DCMAKE_TOOLCHAIN_FILE=<full_path>/vcpkg/scripts/buildsystems/vcpkg.cmake .. 
(see vcpkg documentation for more detailed examples)


Things still to do (in no particular order):
1. review program layout
2. varying draw line thicknesses
3. Add high score record list, display and user input
4. Increase beat frequency as game continues
5. automatic window and game scaling
