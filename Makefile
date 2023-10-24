CC = g++
COMPILE_FLAGS = -Wall -g
SRC_FILES = src/*.cpp \
						src/ecs/*.cpp \
						src/ecs/Elements/*.hpp \
						src/ecs/Systems/*.hpp \
						src/events/*.hpp \
						src/personal/*.hpp

LINKERS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.4
OBJ_NAME = J5E


build:
	$(CC) $(COMPILE_FLAGS) $(SRC_FILES) $(LINKERS) -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

debug:
	gdb $(OBJ_NAME)

clean:
	rm $(OBJNAME)
