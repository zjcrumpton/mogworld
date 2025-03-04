CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -Iinclude

# Helper function to recursively grab files
rwildcard=$(foreach d,$(wildcard $1*),$(filter $(subst *,%,$2),$d) $(call rwildcard,$d/,$2))

# Source files for each target
GAME_SRCS = $(call rwildcard,src/,*.cpp)
GAME_OBJS = $(patsubst src/%.cpp,out/%.o,$(GAME_SRCS))

EDITOR_SRCS = $(call rwildcard,editor/,*.cpp)
EDITOR_OBJS = $(patsubst editor/%.cpp,out/%.o,$(EDITOR_SRCS))

# Final targets
all: out/mogworld out/mogworld_editor

# Game (headless/server/CLI)
out/mogworld: $(GAME_OBJS)
	@mkdir -p out
	$(CXX) $(CXXFLAGS) -o $@ $(GAME_OBJS)

# Editor (Qt GUI)
out/mogworld_editor: $(EDITOR_OBJS)
	@mkdir -p out
	$(CXX) $(CXXFLAGS) -o $@ $(EDITOR_OBJS) `pkg-config --cflags --libs Qt6Widgets`

# Compile rules for both sets of sources
out/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

out/%.o: editor/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) `pkg-config --cflags Qt6Widgets` -c $< -o $@

# Clean rule
clean:
	rm -rf out
