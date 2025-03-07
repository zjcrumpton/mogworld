#ifndef ENGINE_CONTENT_EDITOR_WINDOW_HPP
#define ENGINE_CONTENT_EDITOR_WINDOW_HPP

#include <QMainWindow>
#include "Editors/TraitEditorWindow.hpp"
#include "Editors/MaterialEditorWindow.hpp"

class EngineContentEditorWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit EngineContentEditorWindow(QWidget* main_menu = nullptr, QWidget* parent = nullptr);

private slots:
    void on_edit_traits_clicked();
    void on_edit_materials_clicked();
    void on_back_to_main_menu_clicked();

private:
    QWidget* main_menu;
    TraitEditorWindow* trait_editor_window = nullptr;
    MaterialEditorWindow* material_editor_window = nullptr;
};

#endif