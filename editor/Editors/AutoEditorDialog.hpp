#ifndef AUTOEDITORDIALOG_HPP
#define AUTOEDITORDIALOG_HPP

#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <unordered_map>
#include <string>
#include <typeinfo>
#include <cstddef>
#include <iostream>
#include <QMessageBox>
#include "Core/World/Trait.hpp"
#include "Core/Registries/TraitRegistry.hpp"

template<typename T>
class AutoEditorDialog : public QDialog {
    static_assert(std::is_class_v<T>, "AutoEditorDialog only works with class/struct types");

public:
    explicit AutoEditorDialog(T& target, QWidget* parent = nullptr)
        : QDialog(parent), target(target), layout(new QFormLayout(this)) {
        setLayout(layout);
        setupFields();
        setupButtons();
    }

    void applyChanges() {
        for (const auto& field : T::getFields()) {
            if (!editors.contains(field.name)) continue;

            QWidget* editor = editors[field.name];

            if (field.typeName == typeid(std::string).name()) {
                auto* lineEdit = dynamic_cast<QLineEdit*>(editor);
                if (lineEdit) {
                    *getFieldPtr<std::string>(field.offset) = lineEdit->text().toStdString();
                }
            } else if (field.name == "traits") {
                applyReferenceListChangesFor<TraitReference>(editor, field);
            }
        }
    }

private:
    T& target;
    QFormLayout* layout;
    std::unordered_map<std::string, QWidget*> editors;

    template<typename FieldType>
    FieldType* getFieldPtr(size_t offset) {
        return reinterpret_cast<FieldType*>(reinterpret_cast<char*>(&target) + offset);
    }

    void setupFields() {
        for (const auto& field : T::getFields()) {
            QWidget* editor = nullptr;

            if (field.typeName == typeid(std::string).name()) {
                editor = setupStringEditor(field);
            } else if (field.name == "traits") {
                editor = setupReferenceListEditorFor<TraitReference>(field);
            }

            if (editor) {
                layout->addRow(QString::fromStdString(field.name), editor);
                editors[field.name] = editor;
            } else {
                QMessageBox::warning(this, "Unsupported Field",
                    QString("Cannot edit field '%1' (unsupported type)").arg(QString::fromStdString(field.name)));
            }
        }
    }

    QWidget* setupStringEditor(const FieldInfo& field) {
        auto* lineEdit = new QLineEdit(this);
        lineEdit->setText(QString::fromStdString(*getFieldPtr<std::string>(field.offset)));
        return lineEdit;
    }

    template<typename RefType>
    QListWidget* setupReferenceListEditorFor(const FieldInfo& field) {
        auto* listWidget = new QListWidget(this);
        auto& refs = *getFieldPtr<std::vector<RefType>>(field.offset);

        for (const auto& ref : refs) {
            addReferenceItem<RefType>(listWidget, ref.name);
        }

        addAddButton<RefType>(listWidget);
        return listWidget;
    }

    void setupButtons() {
        auto* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        layout->addRow(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, this, [this]() {
            applyChanges();
            accept();
        });
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    }

    template<typename RefType>
    void applyReferenceListChangesFor(QWidget* editor, const FieldInfo& field) {
        auto* listWidget = dynamic_cast<QListWidget*>(editor);
        if (!listWidget) return;

        auto& refs = *getFieldPtr<std::vector<RefType>>(field.offset);
        refs.clear();

        for (int i = 0; i < listWidget->count() - 1; ++i) {  // Skip last "Add Reference" item
            auto* item = listWidget->item(i);
            auto* rowWidget = dynamic_cast<QWidget*>(listWidget->itemWidget(item));
            if (!rowWidget) continue;

            auto* comboBox = rowWidget->findChild<QComboBox*>();
            if (comboBox) {
                RefType ref;
                ref.name = comboBox->currentText().toStdString();
                refs.push_back(ref);
            }
        }
    }

    template<typename RefType>
    void addReferenceItem(QListWidget* listWidget, const std::string& initialName = "") {
        auto* item = new QListWidgetItem(listWidget);
        auto* rowWidget = new QWidget(listWidget);
        auto* layout = new QHBoxLayout(rowWidget);
        layout->setContentsMargins(0, 0, 0, 0);

        auto* comboBox = new QComboBox(rowWidget);
        for (const auto& name : RefType::Registry::get().get_all_names()) {
            comboBox->addItem(QString::fromStdString(name));
        }
        comboBox->setCurrentText(QString::fromStdString(initialName));

        auto* removeButton = new QPushButton("❌", rowWidget);
        removeButton->setFixedWidth(30);

        QObject::connect(removeButton, &QPushButton::clicked, [listWidget, item]() {
            delete listWidget->takeItem(listWidget->row(item));
            // moveAddButtonToBottom(listWidget);  // Keep "Add Reference" button at the end
        });

        layout->addWidget(comboBox);
        layout->addWidget(removeButton);
        rowWidget->setLayout(layout);

        // Always insert new item above the add button (second-to-last position)
        int addButtonIndex = listWidget->count() - 1;
        listWidget->insertItem(addButtonIndex, item);
        listWidget->setItemWidget(item, rowWidget);

        moveAddButtonToBottom(listWidget);  // Just to be extra safe
    }

    template<typename RefType>
    void addAddButton(QListWidget* listWidget) {
        auto* item = new QListWidgetItem(listWidget);
        auto* addButton = new QPushButton("Add Reference", listWidget);
        addButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        addButton->setStyleSheet("font-size: 12px;");

        connect(addButton, &QPushButton::clicked, this, [=]() {
            addReferenceItem<RefType>(listWidget);
        });

        listWidget->addItem(item);
        listWidget->setItemWidget(item, addButton);
    }

    void moveAddButtonToBottom(QListWidget* listWidget) {
        if (listWidget->count() == 0) return;

        QListWidgetItem* addButtonItem = listWidget->takeItem(listWidget->count() - 1);
        listWidget->addItem(addButtonItem);
        listWidget->setItemWidget(addButtonItem, listWidget->itemWidget(addButtonItem));
    }
};

#endif // AUTOEDITORDIALOG_HPP
