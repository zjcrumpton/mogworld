#ifndef BIOME_REGISTRY_HPP
#define BIOME_REGISTRY_HPP

#include "Core/World/Biome.hpp"
#include "Core/Registries/JsonRegistryBase.hpp"
#include "Core/Macros/SingletonMacro.hpp"
#include "Core/Registries/RegistryReference.hpp"

inline constexpr char BIOME_FILE_PATH[] = "assets/biomes.json";

class BiomeRegistry : public JsonRegistryBase<Biome, BIOME_FILE_PATH> {
    DECLARE_SINGLETON(BiomeRegistry)
};

DEFINE_REGISTRY_REFERENCE(Biome, BiomeRegistry)

#endif // BIOME_REGISTRY_HPP