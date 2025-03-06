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
                    // had to use dynamic cast instead of proper qobject_cast
                    // because this class is templated - should be safe though
                    auto* lineEdit = dynamic_cast<QLineEdit*>(editor);

                    if (lineEdit) {
                        *getFieldPtr<std::string>(field.offset) = lineEdit->text().toStdString();
                    }
                }
                // Add support for other types as needed (int, float, bool)
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
            // Add other field types in the future

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
