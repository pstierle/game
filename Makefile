CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude
LDFLAGS = -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

SRCS = src/main.cpp
SRCS += $(wildcard src/state/*.cpp) $(wildcard src/game/*.cpp) $(wildcard src/entities/*.cpp)

OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

TARGET = td.exe

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	del /Q $(OBJS) $(DEPS) $(TARGET)