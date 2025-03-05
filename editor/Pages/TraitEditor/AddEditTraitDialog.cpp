#include "Pages/TraitEditor/AddEditTraitDialog.hpp"
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QVBoxLayout>

AddEditTraitDialog::AddEditTraitDialog(QWidget* parent)
    : QDialog(parent), name_edit(new QLineEdit(this)), description_edit(new QLineEdit(this))
{
    setWindowTitle("Add Trait");
    setMinimumSize(400, 200);

    auto* form_layout = new QFormLayout();
    form_layout->addRow("Name:", name_edit);
    form_layout->addRow("Description:", description_edit);

    auto* button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(button_box, &QDialogButtonBox::accepted, this, &AddEditTraitDialog::accept);
    connect(button_box, &QDialogButtonBox::rejected, this, &AddEditTraitDialog::reject);

    auto* layout = new QVBoxLayout(this);
    layout->addLayout(form_layout);
    layout->addWidget(button_box);
}

AddEditTraitDialog::AddEditTraitDialog(Trait trait, QWidget* parent)
    : QDialog(parent), name_edit(new QLineEdit(this)), description_edit(new QLineEdit(this))
{
    set_trait(trait);
    setWindowTitle("Edit Trait");
    setMinimumSize(400, 200);

    auto* form_layout = new QFormLayout();
    form_layout->addRow("Name:", name_edit);
    form_layout->addRow("Description:", description_edit);

    auto* button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(button_box, &QDialogButtonBox::accepted, this, &AddEditTraitDialog::accept);
    connect(button_box, &QDialogButtonBox::rejected, this, &AddEditTraitDialog::reject);

    auto* layout = new QVBoxLayout(this);
    layout->addLayout(form_layout);
    layout->addWidget(button_box);
}

void AddEditTraitDialog::set_trait(const Trait& trait) {
    name_edit->setText(QString::fromStdString(trait.name));
    description_edit->setText(QString::fromStdString(trait.description));
    original_name = trait.name;  // Remember the original name in case it's renamed
}

Trait AddEditTraitDialog::get_trait() const {
    Trait trait;
    trait.name = name_edit->text().toStdString();
    trait.description = description_edit->text().toStdString();
    return trait;
}

std::string AddEditTraitDialog::get_original_name() const {
    return original_name;
}
