#ifndef TRAIT_EDITOR_WINDOW_HPP
#define TRAIT_EDITOR_WINDOW_HPP

#include <QMainWindow>
#include <QListWidget>
#include "Core/Registries/TraitRegistry.hpp" 

class TraitEditorWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit TraitEditorWindow(QWidget* parent_window, QWidget* parent = nullptr);

protected:
    void showEvent(QShowEvent* event) override;

private slots:
    void on_add_trait_clicked();
    void on_edit_trait_clicked();
    void on_delete_trait_clicked();
    void on_back_to_content_editor_clicked();

private:
    QWidget* parent_window = nullptr;
    QListWidget* trait_list = nullptr;
    void refresh_trait_list();

};

#endif
