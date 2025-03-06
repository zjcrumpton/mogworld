#ifndef TRAIT_EDITOR_WINDOW_HPP
#define TRAIT_EDITOR_WINDOW_HPP

#include "Editors/GenericEditorWindow.hpp"
#include "Core/Registries/TraitRegistry.hpp"
#include "Core/World/Trait.hpp"

using TraitEditorWindow = GenericEditorWindow<Trait, TraitRegistry>;

#endif // TRAIT_EDITOR_WINDOW_HPP
