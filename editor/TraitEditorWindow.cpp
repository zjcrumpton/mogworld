#include "TraitEditorWindow.hpp"
#include "Core/Registries/TraitRegistry.hpp"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <iostream>

TraitEditorWindow::TraitEditorWindow(QWidget* parent_window, QWidget* parent)
    : QMainWindow(parent), parent_window(parent_window)
{
    setWindowTitle("Mogworld Editor - Trait Editor");
    setMinimumSize(800, 800);
    resize(1000, 800);

    auto* central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    auto* layout = new QVBoxLayout();

    auto* title_label = new QLabel("Trait Editor", this);
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setStyleSheet("font-size: 40px; font-weight: bold;");

    trait_list = new QListWidget(this); 
    refresh_trait_list();           

    auto* add_button = new QPushButton("Add Trait", this);
    auto* edit_button = new QPushButton("Edit Selected Trait", this);
    auto* delete_button = new QPushButton("Delete Selected Trait", this);
    auto* back_button = new QPushButton("Back to Engine Content Editor", this);

    add_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    edit_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    delete_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    back_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    layout->addWidget(title_label);
    layout->addWidget(trait_list);
    layout->addWidget(add_button);
    layout->addWidget(edit_button);
    layout->addWidget(delete_button);
    layout->addWidget(back_button);

    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(15);

    central_widget->setLayout(layout);

    connect(add_button, &QPushButton::clicked, this, &TraitEditorWindow::on_add_trait_clicked);
    connect(edit_button, &QPushButton::clicked, this, &TraitEditorWindow::on_edit_trait_clicked);
    connect(delete_button, &QPushButton::clicked, this, &TraitEditorWindow::on_delete_trait_clicked);
    connect(back_button, &QPushButton::clicked, this, &TraitEditorWindow::on_back_to_content_editor_clicked);
}

void TraitEditorWindow::refresh_trait_list() {
    trait_list->clear();
    for (const auto& trait : TraitRegistry::get().get_all_traits()) {
        trait_list->addItem(QString::fromStdString(trait.name));
    }
}

void TraitEditorWindow::showEvent(QShowEvent* event) {
    QMainWindow::showEvent(event);
    refresh_trait_list();  // Reload every time we show the window
}

void TraitEditorWindow::on_add_trait_clicked() {
    std::cout << "Add Trait Clicked" << std::endl;
    // Placeholder - Add Trait dialog goes here in future

    refresh_trait_list();  // For now just refresh to simulate "something changed"
}

void TraitEditorWindow::on_edit_trait_clicked() {
    std::cout << "Edit Trait Clicked" << std::endl;
    // Placeholder - Edit Trait dialog in future
}

void TraitEditorWindow::on_delete_trait_clicked() {
    auto selected = trait_list->currentItem();
    if (selected) {
        std::string name = selected->text().toStdString();
        std::cout << "Deleting trait: " << name << std::endl;

        TraitRegistry::get().remove_trait(name);
        refresh_trait_list();
    } else {
        std::cout << "No trait selected to delete." << std::endl;
    }
}

void TraitEditorWindow::on_back_to_content_editor_clicked() {
    if (parent_window) {
        parent_window->show();
    }
    close();
}
