CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -Iinclude

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, out/%.o, $(SRCS))

all: out/mogworld

out/mogworld: $(OBJS)
	@mkdir -p out
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

out/%.o: src/%.cpp
	@mkdir -p out
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf out
