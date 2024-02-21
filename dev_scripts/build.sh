cd build
cmake ..
cp compile_commands.json ..
cd ..
. fix_compile_commands.sh
cd build
make -j24
