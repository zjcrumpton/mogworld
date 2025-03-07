#ifndef MATERIAL_REGISTRY_HPP
#define MATERIAL_REGISTRY_HPP

#include "Core/World/Material.hpp"
#include "Macros/SingletonMacro.hpp"
#include "Core/Registries/JsonRegistryBase.hpp"
#include "Core/Registries/RegistryReference.hpp"

inline constexpr char MATERIAL_FILE_PATH[] = "assets/materials.json";

class MaterialRegistry : public JsonRegistryBase<Material, MATERIAL_FILE_PATH> {
    DECLARE_SINGLETON(MaterialRegistry)
};

DEFINE_REGISTRY_REFERENCE(Material, MaterialRegistry)

#endif // MATERIAL_REGISTRY_HPP