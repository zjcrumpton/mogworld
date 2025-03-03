CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -Iinclude

# Helper function to grab files recursively
rwildcard=$(foreach d,$(wildcard $1*),$(filter $(subst *,%,$2),$d) $(call rwildcard,$d/,$2))

SRCS = $(call rwildcard,src/,*.cpp)
OBJS = $(patsubst src/%.cpp,out/%.o,$(SRCS))

all: out/mogworld

out/mogworld: $(OBJS)
	@mkdir -p out
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

out/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf out
