#ifndef DARK_MODE_STYLE_HPP
#define DARK_MODE_STYLE_HPP

#include <QString>

namespace DarkModeStyle {

inline QString global_stylesheet() {
    return R"(
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

        QListWidget {
            background-color: #3c3f41;
            color: #ffffff;
            border: 1px solid #555555;
        }

        QListWidget::item {
            padding: 8px;
        }

        QListWidget::item:selected {
            background-color: #555555;
        }
    )";
}

inline QString buttonStyle() {
    return "font-size: 30px; padding: 10px;";
}

} // namespace DarkModeStyle

#endif // DARK_MODE_STYLE_HPP
