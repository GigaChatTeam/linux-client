# Linux client for GigaChat project
Written in C++ using Qt6Widgets and GigaChat sqlite api

## TODO
* review the UI structure
* replace pointers with smart pointers
* find TODOs in the code and complete them (or put them here)
* channel loading
* steal some code (not really code, but design) from [here](https://github.com/gigachat-team/uchat) (yes they basically have the same name for their organization and basically implement the same thing buuuuuuuuuut ugh whatever)
* Start writing wrappers for [sqlite-orm](https://github.com/GigaChatTeam/sqlite-orm)
* Link the library in CMake (and add some login for chosing static or dynamic linking). DON'T FORGET that one debugging session that you had, either reconfigure cbindgen or do manual substitution (for `extern "C"` specifiers)

### Build prerequisites:
- Of course, linux (maybe I'll be adding windows compatability. Currently incompatible code: get_date in file `scr/utils/misc_functions.cpp`. When Makefile is added, the dynamic linking flags will be incompatible with windows for the time being (if anyone would like to fix it, I'll accept right away))
- - actually, I don't think that compatability matters anymore. I am using libconfig and all of that stuff, so for now windows compatability is deprecated.
- Qt 6
- libconfig
- g++/clang++ compiler
- cmake OR qmake - both work for now. however, CMake is recommended option
- - note: I am pretty sure QMake will be deprecated soon because integrating rust library into here with it may be pretty painful. However, in future I'll see how that goes.
- GNU make 

### Build steps: 
1. clone the repo with submodules (`git clone --recursive https://github.com/GigaChatTeam/linux-client && cd liunux-client`)
2. go to the build directory (`mkdir build && cd build`)
3. run cmake (`cmake ..`) or qmake (`qmake ..`)
4. run make (`make` if you used cmake, `make -f QMakefile` if you used qmake)
5. the executable should be in build the folder after this

### Contributing
For now basically any changes are accepted

