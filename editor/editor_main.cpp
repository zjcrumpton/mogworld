#include "MainMenuWindow.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setStyleSheet(R"(
        QWidget {
            background-color: #2b2b2b;
            color: #e0e0e0;
        }

        QPushButton {
            background-color: #3c3f41;
            color: #ffffff;
            border: 1px solid #555555;
            padding: 10px;
            font-size: 30px;
        }

        QPushButton:hover {
            background-color: #4b4e50;
        }

        QLabel {
            color: #ffffff;
        }
    )"); 
    MainMenuWindow window;
    window.show();

    return app.exec();
}
