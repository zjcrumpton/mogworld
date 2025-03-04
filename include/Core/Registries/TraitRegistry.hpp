#ifndef TRAIT_REGISTRY_HPP
#define TRAIT_REGISTRY_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "Core/World/Trait.hpp"

class TraitRegistry {
public:
    static TraitRegistry& get() {
        static TraitRegistry instance;
        return instance;
    }

    void load();
    void clear();

    bool is_known_trait(const std::string& name) const;
    const Trait* get_trait(const std::string& name) const;
    std::vector<Trait> get_all_traits() const;
    std::vector<std::string> get_all_trait_names() const;

    // Deleted to prevent copies/clones (singletons should only exist once)
    TraitRegistry(const TraitRegistry&) = delete;
    TraitRegistry& operator=(const TraitRegistry&) = delete;

private:
    TraitRegistry() = default;  // Private constructor so no one can manually create it
    ~TraitRegistry() = default;

    std::unordered_map<std::string, Trait> traits;

    void load_traits_from_file(const std::string& path);
};

#endif // TRAIT_REGISTRY_HPP
