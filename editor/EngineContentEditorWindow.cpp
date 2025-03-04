#include "EngineContentEditorWindow.hpp"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <iostream>

EngineContentEditorWindow::EngineContentEditorWindow(QWidget* main_menu, QWidget *parent)
    : QMainWindow(parent), main_menu(main_menu)
{
    setWindowTitle("Mogworld Editor - Engine Content Editor");
    setMinimumSize(800, 800);
    resize(1000, 800);

    auto *central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    auto *layout = new QVBoxLayout();

    auto *title_label = new QLabel("Edit Engine Content", this);
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setStyleSheet("font-size: 40px; font-weight: bold;");

    auto *edit_traits_button = new QPushButton("Edit Traits", this);
    auto *back_button = new QPushButton("Back to Main Menu", this);

    edit_traits_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    back_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    layout->addWidget(title_label);
    layout->addWidget(edit_traits_button);
    layout->addWidget(back_button);

    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(15);

    central_widget->setLayout(layout);

    connect(edit_traits_button, &QPushButton::clicked, this, &EngineContentEditorWindow::on_edit_traits_clicked);
    connect(back_button, &QPushButton::clicked, this, &EngineContentEditorWindow::on_back_to_main_menu_clicked);
}

void EngineContentEditorWindow::on_edit_traits_clicked() {
    std::cout << "Edit Traits Clicked" << std::endl;
    // This is where we’ll soon open the Trait Editor.
}

void EngineContentEditorWindow::on_back_to_main_menu_clicked() {
    std::cout << "Returning to Main Menu" << std::endl;

    if (main_menu) {
        main_menu->show();
    }

    close();
}
