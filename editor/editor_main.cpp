#include "Pages/MainMenu/MainMenuWindow.hpp"
#include "Shared/DarkModeStyle.hpp"
#include "Core/Registries/TraitRegistry.hpp"
#include "Core/Registries/MaterialRegistry.hpp"
#include "Core/Registries/TileRegistry.hpp"
#include "Core/Registries/BiomeRegistry.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
    TraitRegistry::get().load();
    MaterialRegistry::get().load();
    TileRegistry::get().load();
    BiomeRegistry::get().load();

    QApplication app(argc, argv);
    app.setStyleSheet(DarkModeStyle::global_stylesheet()); 
    MainMenuWindow window;
    window.show();

    return app.exec();
}
