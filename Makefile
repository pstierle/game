CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude
LDFLAGS = -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
TARGET = game.exe
CLEAN_CMD = del /Q $(subst /,\,$(OBJS:.o=.o)) $(subst /,\,$(TARGET))

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	LDFLAGS = -Llib -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
	TARGET = game
	CLEAN_CMD = rm -f $(OBJS) $(TARGET)
endif

SRCS = src/main.cpp
SRCS += $(wildcard src/game/*.cpp) $(wildcard src/text/*.cpp) $(wildcard src/sprite/*.cpp) $(wildcard src/utils/*.cpp) $(wildcard src/button/*.cpp) $(wildcard src/item/*.cpp)

OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	$(CLEAN_CMD)