#ifndef MATERIAL_EDITOR_WINDOW_HPP
#define MATERIAL_EDITOR_WINDOW_HPP

#include "Editors/GenericEditorWindow.hpp"
#include "Core/Registries/MaterialRegistry.hpp"
#include "Core/World/Material.hpp"

using MaterialEditorWindow = GenericEditorWindow<Material, MaterialRegistry>;

#endif // MATERIAL_EDITOR_WINDOW_HPP