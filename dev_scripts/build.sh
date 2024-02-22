cd build
cmake ..
cp compile_commands.json ..
cd ..
dev_scripts/fix_compile_commands.sh
cd build
make -j24
