# Linux client for GigaChat project
Written on C++ using Qt framework

### Build prerequisites:
- Of course, linux
- Qt 6 or higher
- g++ compiler
- GNU make 
- GHC Haskell compiler (not necessary yet)
- ghc-static (not necessary yet)
- patience

### Build steps: 
1. clone the repository & navigate to GigaChat/client/desktop/linux-x11/source
2. `haskell/build-shared.sh` or `cd haskell && ghc -dynamic -shared -fPIE <did not finish the command lol>`  (not necessary yet)
3. run `qmake GigaQt.pro && make`
4. Pray. for it to work.

