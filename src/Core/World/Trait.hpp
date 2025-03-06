#ifndef TRAIT_HPP
#define TRAIT_HPP

#include <string>
#include "Macros/ReflectionMacro.hpp"
#include "nlohmann/json.hpp"

struct Trait {
    std::string name;
    std::string description;

    REFLECTABLE(Trait,
        REFLECT_FIELD(std::string, name),
        REFLECT_FIELD(std::string, description)
    )
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Trait, name, description)
};

#endif
