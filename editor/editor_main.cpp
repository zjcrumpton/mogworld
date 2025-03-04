#include "MainMenuWindow.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainMenuWindow window;
    window.show();

    return app.exec();
}
