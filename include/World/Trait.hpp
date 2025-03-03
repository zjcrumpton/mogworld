#ifndef TRAIT_HPP
#define TRAIT_HPP

#include <string>
#include <nlohmann/json.hpp>

struct Trait {
    std::string name;
    std::string description;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Trait, name, description)
};

#endif