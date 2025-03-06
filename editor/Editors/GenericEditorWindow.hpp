#ifndef GENERIC_EDITOR_WINDOW_HPP
#define GENERIC_EDITOR_WINDOW_HPP

#include <QMainWindow>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "Editors/AutoEditorDialog.hpp"
#include <Shared/Message.hpp>

// Generic Editor Window - Works for any T with a "name" field and a corresponding Registry

template<typename T, typename Registry>
class GenericEditorWindow : public QMainWindow {
public:
    explicit GenericEditorWindow(const QString& title, QWidget* parent_window = nullptr, QWidget* parent = nullptr)
        : QMainWindow(parent), parent_window(parent_window) {
        setWindowTitle(title);
        setMinimumSize(800, 800);
        resize(1000, 800);

        auto* central_widget = new QWidget(this);
        setCentralWidget(central_widget);

        auto* layout = new QVBoxLayout();

        auto* title_label = new QLabel(title, this);
        title_label->setAlignment(Qt::AlignCenter);
        title_label->setStyleSheet("font-size: 40px; font-weight: bold;");

        item_list = new QListWidget(this);
        refresh_item_list();

        auto* add_button = new QPushButton("Add", this);
        auto* edit_button = new QPushButton("Edit Selected", this);
        auto* delete_button = new QPushButton("Delete Selected", this);
        auto* back_button = new QPushButton("Back", this);

        layout->addWidget(title_label);
        layout->addWidget(item_list);
        layout->addWidget(add_button);
        layout->addWidget(edit_button);
        layout->addWidget(delete_button);
        layout->addWidget(back_button);

        central_widget->setLayout(layout);

        connect(add_button, &QPushButton::clicked, this, &GenericEditorWindow::on_add_clicked);
        connect(edit_button, &QPushButton::clicked, this, &GenericEditorWindow::on_edit_clicked);
        connect(delete_button, &QPushButton::clicked, this, &GenericEditorWindow::on_delete_clicked);
        connect(back_button, &QPushButton::clicked, this, &GenericEditorWindow::on_back_clicked);
    }

protected:
    void showEvent(QShowEvent* event) override {
        QMainWindow::showEvent(event);
        refresh_item_list();
    }

private:
    QWidget* parent_window = nullptr;
    QListWidget* item_list = nullptr;

    void refresh_item_list() {
        item_list->clear();
        for (const auto& item : Registry::get().get_all()) {
            item_list->addItem(QString::fromStdString(item.name));
        }
    }

    void on_add_clicked() {
        T new_item;
        AutoEditorDialog<T> dialog(new_item, this);

        if (dialog.exec() == QDialog::Accepted) {
            dialog.applyChanges();

            auto& registry = Registry::get();
            if (registry.is_known(new_item.name)) {
                Message::show_error("Item already exists with name: " + new_item.name + ".", this);
            } else {
                registry.add_or_update(new_item);
                refresh_item_list();
            }
        }
    }

    void on_edit_clicked() {
        auto selected = item_list->currentItem();
        if (!selected) {
            Message::show_error("No item selected for editing.", this);
            return;
        }

        std::string old_name = selected->text().toStdString();
        const T* existing_item = Registry::get().find_by_name(old_name);
        if (!existing_item) {
            Message::show_error("Selected item not found in registry.", this);
            return;
        }

        T editable_item = *existing_item;
        AutoEditorDialog<T> dialog(editable_item, this);

        if (dialog.exec() == QDialog::Accepted) {
            dialog.applyChanges();

            auto& registry = Registry::get();
            if (editable_item.name != old_name) {
                registry.remove(old_name);
            }
            registry.add_or_update(editable_item);
            refresh_item_list();
        }
    }

    void on_delete_clicked() {
        auto* selected_item = item_list->currentItem();
        if (selected_item) {
            std::string name = selected_item->text().toStdString();
            Registry::get().remove(name);
            refresh_item_list();
        } else {
            Message::show_error("No item selected to delete.", this);
        }
    }

    void on_back_clicked() {
        if (parent_window) {
            parent_window->show();
        }
        close();
    }
};

#endif // GENERIC_EDITOR_WINDOW_HPP
