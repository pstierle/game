CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude
LDFLAGS = -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image

SRCS = src/main.cpp
SRCS += $(wildcard src/game/*.cpp) $(wildcard src/text/*.cpp) $(wildcard src/sprite/*.cpp) $(wildcard src/utils/*.cpp) $(wildcard src/button/*.cpp) $(wildcard src/item/*.cpp)

OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

TARGET = game.exe

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	del /Q $(subst /,\,$(OBJS:.o=.o)) $(subst /,\,$(TARGET))



# CXX = g++

# CXXFLAGS = -Wall -Wextra -std=c++11

# SRC_DIR = src
# SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard src/entities/*.cpp) $(wildcard src/state/*.cpp)
# OBJ_DIR = output
# OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# EXE_NAME = td

# SDL_INCLUDE = -I include -I include/SDL2
# SDL_LIB = -L lib -lSDL2 -lSDL2_ttf

# all: $(EXE_NAME)

# $(EXE_NAME): $(OBJ_FILES)
# 	$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $(EXE_NAME) $(SDL_LIB)

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
# 	@mkdir -p $(@D)
# 	$(CXX) $(CXXFLAGS) -c $< -o $@ $(SDL_INCLUDE)

# clean:
# 	rm -rf $(OBJ_DIR) $(EXE_NAME)