#include "Core/Registries/TraitRegistry.hpp"
#include <fstream>
#include "nlohmann/json.hpp"
#include <iostream>

void TraitRegistry::load() {
    clear();
    load_traits_from_file("assets/traits.json");
}

void TraitRegistry::clear() {
    traits.clear();
}

void TraitRegistry::add_or_update_trait(const Trait& trait) {
    traits[trait.name] = trait;
    save_traits_to_file("assets/traits.json");  // Automatically save after any change
}

void TraitRegistry::remove_trait(const std::string& name) {
    traits.erase(name);
    save_traits_to_file("assets/traits.json");  // Automatically save after any change
}

bool TraitRegistry::is_known_trait(const std::string& name) const {
    return traits.find(name) != traits.end();
}

const Trait* TraitRegistry::get_trait(const std::string& name) const {
    auto it = traits.find(name);
    if (it != traits.end()) {
        return &it->second;
    }
    return nullptr;
}

std::vector<Trait> TraitRegistry::get_all_traits() const {
    std::vector<Trait> all;
    all.reserve(traits.size());
    for (const auto& pair : traits) {
        all.push_back(pair.second);
    }
    return all;
}

std::vector<std::string> TraitRegistry::get_all_trait_names() const {
    std::vector<std::string> names;
    names.reserve(traits.size());
    for (const auto& pair : traits) {
        names.push_back(pair.first);
    }
    return names;
}

void TraitRegistry::load_traits_from_file(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open traits file: " + path);
    }

    nlohmann::json json;
    file >> json;

    auto loaded_traits = json.get<std::vector<Trait>>();
    for (const auto& trait : loaded_traits) {
        traits[trait.name] = trait;
    }

    std::cout << "Loaded " << loaded_traits.size() << " traits from " << path << std::endl;
}

void TraitRegistry::save_traits_to_file(const std::string& path) const {
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open traits file for writing: " + path);
    }

    std::vector<Trait> all_traits;
    all_traits.reserve(traits.size());
    for (const auto& [name, trait] : traits) {
        all_traits.push_back(trait);
    }

    nlohmann::json json = all_traits;
    file << json.dump(4);
}
