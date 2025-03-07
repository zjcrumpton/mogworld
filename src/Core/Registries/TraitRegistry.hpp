#ifndef TRAIT_REGISTRY_HPP
#define TRAIT_REGISTRY_HPP

#include "Core/World/Trait.hpp"
#include "Macros/SingletonMacro.hpp"
#include "Core/Registries/JsonRegistryBase.hpp"
#include "Core/Registries/RegistryReference.hpp"

inline constexpr char TRAIT_FILE_PATH[] = "assets/traits.json";

class TraitRegistry : public JsonRegistryBase<Trait, TRAIT_FILE_PATH> {
    DECLARE_SINGLETON(TraitRegistry)
};

DEFINE_REGISTRY_REFERENCE(Trait, TraitRegistry)

#endif // TRAIT_REGISTRY_HPP
