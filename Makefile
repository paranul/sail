CFLAGS += -std=c99 -Wpedantic -pedantic-errors
CFLAGS += -Werror
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Waggregate-return
CFLAGS += -Wbad-function-cast
CFLAGS += -Wcast-align
CFLAGS += -Wcast-qual
CFLAGS += -Wdeclaration-after-statement
CFLAGS += -Wfloat-equal
CFLAGS += -Wformat=2
CFLAGS += -Wlogical-op
CFLAGS += -Wmissing-declarations
CFLAGS += -Wmissing-include-dirs
CFLAGS += -Wmissing-prototypes
CFLAGS += -Wnested-externs
CFLAGS += -Wpointer-arith
CFLAGS += -Wredundant-decls
CFLAGS += -Wsequence-point
CFLAGS += -Wshadow
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wswitch
CFLAGS += -Wundef
CFLAGS += -Wunreachable-code
CFLAGS += -Wunused-but-set-parameter
CFLAGS += -Wwrite-strings

CXXFLAGS += -pedantic
CXXFLAGS += -Wall
CXXFLAGS += -Wextra
CXXFLAGS += -Wcast-align
CXXFLAGS += -Wcast-qual
CXXFLAGS += -Wctor-dtor-privacy
CXXFLAGS += -Wdisabled-optimization
CXXFLAGS += -Wformat=2
CXXFLAGS += -Winit-self
CXXFLAGS += -Wlogical-op
CXXFLAGS += -Wswitch-default
CXXFLAGS += -Wundef
CXXFLAGS += -Wsign-promo
CXXFLAGS += -Wstrict-null-sentinel
CXXFLAGS += -Wstrict-overflow=5
CXXFLAGS += -Wswitch-default
CXXFLAGS += -Wundef
#CXXFLAGS += -Werror
CXXFLAGS += -Wunused



################################################################################
# Declare some Makefile variables
################################################################################
CC = g++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I"./include"
SRC_FILES = ./src/*.cpp \
		./src/ECS/*.cpp \
		./src/ECSComponents/*.cpp \
		./src/testSource/*.cpp \
		#./src/ECSSystems/*.cpp \
			# ./src/*.cpp \
			# ./src/Logger/*.cpp \
			# ./src/ECS/*.cpp \
			# ./src/AssetStore/*.cpp
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3 
OBJ_NAME = engine

################################################################################
# Declare some Makefile rules
################################################################################
build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(SRC_FILES) $(LINKER_FLAGS) -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
