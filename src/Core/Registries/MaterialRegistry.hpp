#ifndef MATERIAL_REGISTRY_HPP
#define MATERIAL_REGISTRY_HPP

#include "Core/World/Material.hpp"
#include "Macros/SingletonMacro.hpp"
#include "Core/Registries/JsonRegistryBase.hpp"

inline constexpr char FILE_PATH[] = "assets/materials.json";

class MaterialRegistry : public JsonRegistryBase<Material, FILE_PATH> {
    DECLARE_SINGLETON(MaterialRegistry)
};

#endif // MATERIAL_REGISTRY_HPP