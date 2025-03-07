#ifndef TRAIT_HPP
#define TRAIT_HPP

#include <string>
#include "Core/Macros/ReflectionMacro.hpp"

struct Trait {
    std::string name;
    std::string description;

    REFLECT(Trait, name, description)
};

#endif // TRAIT_HPP
