#include <iostream>
#include "Core/Registries/TraitRegistry.hpp"

int main() {
    std::cout << "<<< MogWorld Engine V0.0.1 >>>" << std::endl;
    TraitRegistry trait_registery;
    trait_registery.load();
    for (const auto& name : trait_registery.get_all_trait_names()) {
        std::cout << " - " << name << std::endl;
    }
    return 0;
}