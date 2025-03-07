#ifndef TILE_INSTANCE_HPP
#define TILE_INSTANCE_HPP

#include "Core/Registries/TileRegistry.hpp"
#include "Core/Macros/ReflectionMacro.hpp"

struct TileInstance {
    TileReference tile;
    float elevation;
    // cached walkability - initialized from Tile but
    // can be overridden by gameplay events possibly
    bool is_walkable;
    // same considerations as above
    bool blocks_vision;

    REFLECT(TileInstance, tile, elevation, is_walkable, blocks_vision)
};

#endif