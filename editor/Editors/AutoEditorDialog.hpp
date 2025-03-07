#ifndef AUTOEDITORDIALOG_HPP
#define AUTOEDITORDIALOG_HPP

#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDialogButtonBox>
#include <unordered_map>
#include <string>
#include <typeinfo>
#include <cstddef>
#include <iostream>
#include <QMessageBox>
#include <QListWidget>
#include <QComboBox>
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
            if (editors.find(field.name) != editors.end()) {
                QWidget* editor = editors[field.name];
                if (field.typeName == typeid(std::string).name()) {
                    auto* lineEdit = dynamic_cast<QLineEdit*>(editor);
                    if (lineEdit) {
                        *getFieldPtr<std::string>(field.offset) = lineEdit->text().toStdString();
                    }
                } else if (field.typeName == typeid(std::vector<Trait>).name()) {
                    auto* listWidget = dynamic_cast<QListWidget*>(editor);
                    if (listWidget) {
                        auto& targetVector = *getFieldPtr<std::vector<Trait>>(field.offset);
                        targetVector.clear();

                        for (int i = 0; i < listWidget->count(); ++i) {
                            auto* item = listWidget->item(i);
                            auto* comboBox = dynamic_cast<QComboBox*>(listWidget->itemWidget(item));
                            if (comboBox) {
                                std::string selectedName = comboBox->currentText().toStdString();
                                const Trait* foundTrait = TraitRegistry::get().find_by_name(selectedName);
                                if (foundTrait) {
                                    targetVector.push_back(*foundTrait);
                                }
                            }
                        }
                    }
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
            } else if (field.typeName == typeid(std::vector<Trait>).name()) {
                auto* listWidget = new QListWidget(this);
                auto& traits = *getFieldPtr<std::vector<Trait>>(field.offset);

                for (const auto& trait : traits) {
                    auto* item = new QListWidgetItem(listWidget);
                    auto* comboBox = new QComboBox(listWidget);

                    for (const auto& regTrait : TraitRegistry::get().get_all()) {
                        comboBox->addItem(QString::fromStdString(regTrait.name));
                    }
                    comboBox->setCurrentText(QString::fromStdString(trait.name));

                    listWidget->addItem(item);
                    listWidget->setItemWidget(item, comboBox);
                }

                layout->addRow(QString::fromStdString(field.name), listWidget);
                editors[field.name] = listWidget;
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
};

#endif // AUTOEDITORDIALOG_HPP
