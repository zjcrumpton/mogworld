#ifndef TRAIT_REGISTRY_HPP
#define TRAIT_REGISTRY_HPP

#include "Core/World/Trait.hpp"
#include "Macros/SingletonMacro.hpp"
#include "Core/Registries/JsonRegistryBase.hpp"

inline constexpr char FILE_PATH[] = "assets/traits.json";

class TraitRegistry : public JsonRegistryBase<Trait, FILE_PATH> {
    DECLARE_SINGLETON(TraitRegistry)
};

#endif // TRAIT_REGISTRY_HPP
