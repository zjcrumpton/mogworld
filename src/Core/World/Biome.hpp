#ifndef BIOME_HPP
#define BIOME_HPP

#include <string>
#include "Core/Registries/TileRegistry.hpp"
#include "Core/Macros/ReflectionMacro.hpp"

struct Biome {
    std::string name;
    // Primary floor tile for this biome
    TileReference base_floor;
    // Occasional visual variety floor tile (IE dirt patches in grassland)
    TileReference secondary_floor;
    // Chance (0.0-1.0) of placing a secondary floor tile instead of base
    float secondary_chance;
    // Floor to place along water edges (IE mud in swamps, sand on beaches)
    TileReference water_edge_floor;
    // What elevation range this biome prefers (IE 0.0-0.4 = lowlands)
    float elevation_min;
    float elevation_max;
    // Wetness (dry, normal, wet)
    std::string moisture;

    REFLECT(Biome, name, base_floor, secondary_floor, secondary_chance, water_edge_floor, elevation_min, elevation_max, moisture)
};

#endif
