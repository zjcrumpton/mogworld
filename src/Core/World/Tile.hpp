#ifndef TILE_HPP
#define TILE_HPP

#include <string>
#include "Core/Registries/MaterialRegistry.hpp"
#include "Core/Macros/ReflectionMacro.hpp"

struct Tile {
    std::string name;
    MaterialReference material;
    bool is_walkable;
    bool blocks_vision;

    // Helper Data
    std::string editor_color;

    REFLECT(Tile, name, material, is_walkable, blocks_vision, editor_color)
};

#endif