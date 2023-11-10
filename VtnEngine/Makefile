APP_NAME = MyApp
BUILD_DIR = ./bin
CPP_FILES = ./src/*.cpp

APP_DEFINES:=
APP_INCLUDES:=
APP_LINKERS:=

build:
	g++ -std=c++17 $(CPP_FILES) -o $(BUILD_DIR)/$(APP_NAME) -Wall -I include -lsdl2 -lsdl2_ttf -lsdl2_image

run:
	$(BUILD_DIR)/$(APP_NAME)