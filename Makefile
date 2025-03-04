# Compiler setup
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -Iinclude -Ieditor
MOC = /usr/lib/qt6/libexec/moc

# Helper to recursively find files
rwildcard = $(foreach d,$(wildcard $1*),$(filter $(subst *,%,$2),$d) $(call rwildcard,$d/,$2))

# Game sources (only the src folder)
GAME_SRCS = $(call rwildcard,src/,*.cpp)
GAME_OBJS = $(patsubst src/%.cpp,out/%.o,$(GAME_SRCS))

# Editor sources (Qt-based UI) + Core files needed by editor (like TraitRegistry)
EDITOR_SRCS = $(call rwildcard,editor/,*.cpp) $(call rwildcard,src/Core/Registries/,*.cpp)
EDITOR_OBJS = $(patsubst src/%.cpp,out/%.o,$(filter src/Core/Registries/%, $(EDITOR_SRCS))) \
              $(patsubst editor/%.cpp,out/%.o,$(filter editor/%, $(EDITOR_SRCS)))

# MOC handling
MOC_HEADERS = $(call rwildcard,editor/,*.hpp) $(call rwildcard,editor/,*.h)
MOC_CPP = $(patsubst editor/%.h,out/moc_%.cpp,$(filter %.h,$(MOC_HEADERS))) \
          $(patsubst editor/%.hpp,out/moc_%.cpp,$(filter %.hpp,$(MOC_HEADERS)))
MOC_OBJS = $(patsubst out/%.cpp,out/%.o,$(MOC_CPP))

# Add MOC objects to editor build
EDITOR_OBJS += $(MOC_OBJS)

# Final targets
all: out/mogworld out/mogworld_editor

# Game target (headless/server/CLI)
out/mogworld: $(GAME_OBJS)
	@mkdir -p out
	$(CXX) $(CXXFLAGS) -o $@ $^

# Editor target (Qt GUI)
out/mogworld_editor: $(EDITOR_OBJS)
	@mkdir -p out
	$(CXX) $(CXXFLAGS) -o $@ $^ `pkg-config --cflags --libs Qt6Widgets`

# Compile rules for regular game sources
out/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile rules for editor sources
out/%.o: editor/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) `pkg-config --cflags Qt6Widgets` -c $< -o $@

# MOC rules
out/moc_%.cpp: editor/%.h
	@mkdir -p $(dir $@)
	$(MOC) $< -o $@

out/moc_%.cpp: editor/%.hpp
	@mkdir -p $(dir $@)
	$(MOC) $< -o $@

out/moc_%.o: out/moc_%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) `pkg-config --cflags Qt6Widgets` -c $< -o $@

# Clean
clean:
	rm -rf out
