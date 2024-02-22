# Linux client for GigaChat project
Written in C++ using Qt6Widgets and GigaChat sqlite api

### Build prerequisites:
- Of course, linux (maybe I'll be adding windows compatability. Currently incompatible code: get_date in file `scr/utils/misc_functions.cpp`. When Makefile is added, the dynamic linking flags will be incompatible with windows for the time being (if anyone would like to fix it, I'll accept right away))
- Qt 6
- libconfig
- g++/clang++ compiler
- cmake OR qmake - both work for now. however, CMake is recommended option
- GNU make 

### Build steps: 
1. clone the repo with submodules (`git clone --recursive https://github.com/GigaChatTeam/linux-client && cd liunux-client`)
2. go to the build directory (`mkdir build && cd build`)
3. run cmake (`cmake ..`) or qmake (`qmake ..`)
4. run make (`make` if you used cmake, `make -f QMakefile` if you used qmake)
5. the executable should be in build the folder after this

### Contributing
For now basically any changes are accepted

