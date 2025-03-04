#include <iostream>
#include "Core/Registries/TraitRegistry.hpp"

int main() {
    std::cout << "<<< MogWorld Engine V0.0.1 >>>" << std::endl;
    TraitRegistry::get().load();

    return 0;
}