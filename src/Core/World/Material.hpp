#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <vector>
#include "Core/World/Trait.hpp"
#include "Macros/ReflectionMacro.hpp"
#include "Core/Registries/TraitRegistry.hpp"

struct Material {
    std::string name;
    std::string description;
    std::vector<TraitReference> traits;
 
    REFLECT(Material, name, description, traits)
};

#endif // MATERIAL_HPP