#ifndef TILE_REGISTRY_HPP
#define TILE_REGISTRY_HPP

#include "Core/World/Tile.hpp"
#include "Core/Registries/JsonRegistryBase.hpp"
#include "Core/Macros/SingletonMacro.hpp"
#include "Core/Registries/RegistryReference.hpp"

inline constexpr char TILE_FILE_PATH[] = "assets/tiles.json";

class TileRegistry : public JsonRegistryBase<Tile, TILE_FILE_PATH> {
    DECLARE_SINGLETON(TileRegistry)
};

DEFINE_REGISTRY_REFERENCE(Tile, TileRegistry)

#endif // TILE_REGISTRY_HPP