#include "TraitEditorWindow.hpp"
#include "Core/Registries/TraitRegistry.hpp"
#include "Pages/EngineContentEditor/AutoEditorDialog.hpp"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include <Shared/Message.hpp>
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

    layout->addWidget(title_label);
    layout->addWidget(trait_list);
    layout->addWidget(add_button);
    layout->addWidget(edit_button);
    layout->addWidget(delete_button);
    layout->addWidget(back_button);

    central_widget->setLayout(layout);

    connect(add_button, &QPushButton::clicked, this, &TraitEditorWindow::on_add_trait_clicked);
    connect(edit_button, &QPushButton::clicked, this, &TraitEditorWindow::on_edit_trait_clicked);
    connect(delete_button, &QPushButton::clicked, this, &TraitEditorWindow::on_delete_trait_clicked);
    connect(back_button, &QPushButton::clicked, this, &TraitEditorWindow::on_back_to_content_editor_clicked);
}

void TraitEditorWindow::refresh_trait_list() {
    trait_list->clear();
    for (const auto& trait : TraitRegistry::get().get_all()) {
        trait_list->addItem(QString::fromStdString(trait.name));
    }
}

void TraitEditorWindow::showEvent(QShowEvent* event) {
    QMainWindow::showEvent(event);
    refresh_trait_list();
}

void TraitEditorWindow::on_add_trait_clicked() {
    Trait new_trait;
    AutoEditorDialog<Trait> dialog(new_trait, this);

    if (dialog.exec() == QDialog::Accepted) {
        dialog.applyChanges();

        auto& registry = TraitRegistry::get();
        if (registry.is_known(new_trait.name)) {
            Message::show_error("Trait already exists with name: " + new_trait.name + ".", this);
        } else {
            registry.add_or_update(new_trait);
            refresh_trait_list();
        }
    }
}

void TraitEditorWindow::on_edit_trait_clicked() {
    auto selected = trait_list->currentItem();
    if (!selected) {
        Message::show_error("No trait selected for editing.", this);
        return;
    }

    std::string old_name = selected->text().toStdString();
    const Trait* existing_trait = TraitRegistry::get().find_by_name(old_name);
    if (!existing_trait) {
        Message::show_error("Selected trait not found in registry.", this);
        return;
    }

    // Copy the trait because it's immutable in the registry.
    Trait editable_trait = *existing_trait;

    // Open the editor dialog with the copy.
    AutoEditorDialog<Trait> dialog(editable_trait, this);

    if (dialog.exec() == QDialog::Accepted) {
        dialog.applyChanges();

        auto& registry = TraitRegistry::get();

        if (editable_trait.name != old_name) {
            registry.remove(old_name);  // Name changed — remove old one
        }

        registry.add_or_update(editable_trait);
        refresh_trait_list();
    }
}

void TraitEditorWindow::on_delete_trait_clicked() {
    auto* selected_item = trait_list->currentItem();
    if (selected_item) {
        std::string name = selected_item->text().toStdString();
        TraitRegistry::get().remove(name);
        refresh_trait_list();
    } else {
        Message::show_error("No trait selected to delete.", this);
    }
}

void TraitEditorWindow::on_back_to_content_editor_clicked() {
    if (parent_window) {
        parent_window->show();
    }
    close();
}
