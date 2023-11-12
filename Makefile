
RUST_FILES = $(wildcard rust/*)
CPP_FILES = $(wildcard src/*.cpp) $(wildcard src/*.h)
OBJDIR = .build/common

all: rust cpp
	echo building All targets


rust: $(RUST_FILES)
	echo building Rust libraries


cpp: $(CPP_FILES)
	echo building C++ libraries
	
# TODO: add actual build steps and build directory
# TODO: basically make makefile proper
