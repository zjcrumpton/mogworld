#ifndef TRAIT_REGISTRY_HPP
#define TRAIT_REGISTRY_HPP

#include <string>
#include "Core/World/Trait.hpp"

class TraitRegistry {
public:
    void load();
    void clear();

    bool is_known_trait(const std::string& name) const;
    const Trait* get_trait(const std::string& name) const;
    std::vector<Trait> get_all_traits() const;
    std::vector<std::string> get_all_trait_names() const;

private:
    std::unordered_map<std::string, Trait> traits;
    void load_traits_from_file(const std::string& path);
    
};

#endif