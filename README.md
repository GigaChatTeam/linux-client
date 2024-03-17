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
- Of course, linux 
- - actually, I don't think that compatability matters anymore. I am using libconfig and all of that stuff, so for now windows compatability is deprecated.
- Qt 6
- libconfig (libconfig++, specifically)
- g++/clang++ compiler
- cmake OR qmake - both work for now. however, CMake is recommended option
- - note: I am deprecating QMake support soon because integrating rust library there will be pretty painful. However, in future I'll see how that goes.
- GNU make 

### Build steps: 
1. clone the repo with submodules (`git clone --recursive https://github.com/GigaChatTeam/linux-client && cd liunux-client`)
2. go to the build directory (`mkdir build && cd build`)
3. run cmake (`cmake ..`) or qmake (`qmake ..`)
4. run make (`make` if you used cmake, `make -f QMakefile` if you used qmake. 
    * If your CPU has 256 cores, the recommended option is to run `make -j256`
5. the executable should be in the build folder after this

### Installation:
For the program to be at least somewhat secure without a password, you NEED to
1. create a system group (`GROUP=gigachat && groupadd -r $GROUP`). DO NOT add any users to that group (even yourself!)
2. set client executable to be owned by that group  (`EXEC=/opt/gigachat/gigaqt && chown :$GROUP $EXEC`)
3. add `setgid` to the permissions of the executable (`chmod 2755 $EXEC` or `chmod g+s $EXEC`)
4. create cache folder that is owned by the group you just created (`CACHE=/var/cache/gigachat && mkdir $CACHE && chown root:$GROUP $CACHE`)
5. allow only owning group to access the cache folder (`chmod 070 $CACHE`) 

For simplicity of installation and mangement, these steps should be taken even if you are using password authentication (and, consequently, encryption). There is never too much security.

- This should prevent any applications from accessing cached information, unless they are added to gigachat group. Other scripts can still launch client through shell, but they shouldn't be able to get any information from this (at least I hope so, because implementing security vulnerabilities in C++ is pretty easy.)
- If you want to implement/install your own application that operates over the same cache as this client, just add the executable to the group you created. Only do this if you trust the application <br>

TODO: add these steps to install target

### Contributing
For now basically any changes are accepted

