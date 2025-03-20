CXX=g++
CFLAGS=-O2 -std=c++20

ENTRY=src/main.cpp

ENGINE_SOURCE=src/engine/source/**

ASSETS_DIR=./assets

SDL2_LIBS_LINUX=./libs/libLinux
SDL2_LIBS_WINDOWS=./libs/libWindows

BUILD_DIR=./build
BUILD_LIBS=./build/libs

LINUX_BUILD_FLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lGL -Wl,-rpath=./libs/libLinux/ -L./libs/libLinux/

linux:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_LIBS)
	cp -r $(SDL2_LIBS_LINUX) $(BUILD_LIBS)
	cp -r $(ASSETS_DIR) $(BUILD_DIR)

	$(CXX) $(CFLAGS) $(ENTRY) $(ENGINE_SOURCE) -o $(BUILD_DIR)/main $(LINUX_BUILD_FLAGS)

linuxtest:
	cd $(BUILD_DIR) && ./main > output.log



clean:
	rm -rf $(BUILD_DIR)
