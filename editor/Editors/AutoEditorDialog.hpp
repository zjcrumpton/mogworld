#ifndef AUTOEDITORDIALOG_HPP
#define AUTOEDITORDIALOG_HPP

#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QComboBox>
#include <unordered_map>
#include <string>
#include <typeinfo>
#include <cstddef>
#include <iostream>
#include <QMessageBox>

// Core trait and material references (expand this list if you add more later)
#include "Core/World/Trait.hpp"
#include "Core/World/Material.hpp"

// This is the key — each Reference<> defines its own `TargetType` and `Registry`.
#include "Core/Registries/TraitRegistry.hpp"
#include "Core/Registries/MaterialRegistry.hpp"

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
            if (editors.find(field.name) != editors.end()) {
                QWidget* editor = editors[field.name];

                if (field.typeName == typeid(std::string).name()) {
                    auto* lineEdit = dynamic_cast<QLineEdit*>(editor);
                    if (lineEdit) {
                        *getFieldPtr<std::string>(field.offset) = lineEdit->text().toStdString();
                    }
                } 
                else if (is_reference_vector_field(field)) {
                    applyReferenceListChanges(field, editor);
                }
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
                auto* lineEdit = new QLineEdit(this);
                lineEdit->setText(QString::fromStdString(*getFieldPtr<std::string>(field.offset)));
                editor = lineEdit;
            } 
            else if (is_reference_vector_field(field)) {
                auto* listWidget = new QListWidget(this);
                setupReferenceListEditor(listWidget, field);
                editor = listWidget;
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

    void setupButtons() {
        auto* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        layout->addRow(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, this, [this]() {
            accept();
        });
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    }

    bool is_reference_vector_field(const FieldInfo& field) const {
        return field.typeName.find("Reference") != std::string::npos &&
               field.typeName.find("vector") != std::string::npos;
    }

    // Helper to call the correct editor setup based on field name
    void setupReferenceListEditor(QListWidget* listWidget, const FieldInfo& field) {
        if (field.name == "traits") {
            setupReferenceListEditorFor<TraitReference>(listWidget, field);
        } 
        else if (field.name == "materials") {
            setupReferenceListEditorFor<MaterialReference>(listWidget, field);
        } 
        else {
            QMessageBox::warning(this, "Unsupported Reference Field",
                                 QString("Cannot edit reference field '%1' (no known handler)")
                                 .arg(QString::fromStdString(field.name)));
        }
    }

    // Generic list setup for any Reference<T>
    template<typename RefType>
    void setupReferenceListEditorFor(QListWidget* listWidget, const FieldInfo& field) {
        auto& refs = *getFieldPtr<std::vector<RefType>>(field.offset);

        for (const auto& ref : refs) {
            auto* item = new QListWidgetItem(listWidget);
            auto* comboBox = new QComboBox(listWidget);

            for (const auto& name : RefType::Registry::get().get_all_names()) {
                comboBox->addItem(QString::fromStdString(name));
            }

            comboBox->setCurrentText(QString::fromStdString(ref.name));
            listWidget->addItem(item);
            listWidget->setItemWidget(item, comboBox);
        }
    }

    void applyReferenceListChanges(const FieldInfo& field, QWidget* editor) {
        auto* listWidget = dynamic_cast<QListWidget*>(editor);
        if (!listWidget) return;

        if (field.name == "traits") {
            applyReferenceListChangesFor<TraitReference>(listWidget, field);
        } 
        else if (field.name == "materials") {
            applyReferenceListChangesFor<MaterialReference>(listWidget, field);
        }
    }

    template<typename RefType>
    void applyReferenceListChangesFor(QListWidget* listWidget, const FieldInfo& field) {
        auto& refs = *getFieldPtr<std::vector<RefType>>(field.offset);
        refs.clear();

        for (int i = 0; i < listWidget->count(); ++i) {
            auto* item = listWidget->item(i);
            auto* comboBox = dynamic_cast<QComboBox*>(listWidget->itemWidget(item));
            if (comboBox) {
                RefType ref;
                ref.name = comboBox->currentText().toStdString();
                refs.push_back(ref);
            }
        }
    }
};

#endif // AUTOEDITORDIALOG_HPP
