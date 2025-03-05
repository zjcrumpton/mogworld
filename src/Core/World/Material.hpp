#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <vector>
#include "Core/World/Trait.hpp"
#include "nlohmann/json.hpp"

struct Material {
    std::string name;
    std::string description;
    std::vector<Trait> traits;
   
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Material, name, description, traits)
};

#endif // MATERIAL_HPP