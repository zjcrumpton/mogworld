#ifndef ADD_EDIT_TRAIT_DIALOG_HPP
#define ADD_EDIT_TRAIT_DIALOG_HPP

#include <QDialog>
#include "Core/World/Trait.hpp"

class QLineEdit;

class AddEditTraitDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddEditTraitDialog(QWidget* parent = nullptr);
    explicit AddEditTraitDialog(Trait trait, QWidget* parent = nullptr);

    void set_trait(const Trait& trait);
    Trait get_trait() const;
    std::string get_original_name() const;

private:
    QLineEdit* name_edit;
    QLineEdit* description_edit;
    std::string original_name;
};

#endif // ADD_EDIT_TRAIT_DIALOG_HPP
