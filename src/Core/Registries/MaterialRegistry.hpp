#ifndef MATERIAL_REGISTRY_HPP
#define MATERIAL_REGISTRY_HPP

#include <unordered_map>
#include <string>
#include "Core/World/Material.hpp"

class MaterialRegistry {
public:
    void load();

private:
    std::unordered_map<std::string, Material> materials;
};

#endif // MATERIAL_REGISTRY_HPP