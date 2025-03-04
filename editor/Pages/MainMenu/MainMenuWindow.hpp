#ifndef MAIN_MENU_WINDOW_HPP
#define MAIN_MENU_WINDOW_HPP

#include <QMainWindow>

class MainMenuWindow : public QMainWindow {
    Q_OBJECT

public:
    MainMenuWindow(QWidget *parent = nullptr);
private slots:
    void on_edit_engine_content_clicked();
    void on_create_edit_project_clicked();
    void on_run_project_clicked();
    void on_mod_tools_clicked();
    void on_quit_clicked();

};

#endif