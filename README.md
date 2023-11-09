# Linux client for GigaChat project
Written on C++ using Qt framework

### Build prerequisites:
- Of course, linux (maybe I'll be adding windows compatability. Currently incompatible code: get_date in file `scr/utils/misc_functions.cpp`. When Makefile is added, the dynamic linking flags will be incompatible with windows for the time being (if anyone would like to fix it, I'll accept right away))
- Qt 6 or higher
- g++ compiler
- GNU make 
- ~~GHC Haskell compiler (not necessary yet)~~
- ~~ghc-static (not necessary yet)~~
- patience
- GNU Make if you care for your sanity

### Build steps: 
NOTE: I am planning on adding a Makefile for this, so the most obvoius thing to do would be:
1. `make`

However, if you want to compile it manually, here are the steps:
1. clone the repository & navigate to GigaChat/client/desktop/linux-x11/source
2. ~~`haskell/build-shared.sh` or `cd haskell && ghc -dynamic -shared -fPIE <did not finish the command lol>`  (not necessary yet)~~
3. run `qmake GigaQt.pro && make`
4. Pray. for it to work.

