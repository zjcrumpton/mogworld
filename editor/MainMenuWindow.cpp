#include "MainMenuWindow.hpp"
#include <QVBoxLayout>
#include <QPushButton>
#include <QApplication>
#include <iostream>

MainMenuWindow::MainMenuWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Mogworld Editor - Main Menu");

    auto *central_widget = new QWidget(this);
    auto *layout = new QVBoxLayout();

    auto *edit_button = new QPushButton("Edit Engine Content", this);
    auto *project_button = new QPushButton("Create or Edit a Game Project", this);
    auto *mod_button = new QPushButton("Mod Tools", this);
    auto *run_button = new QPushButton("Run Game Project", this);
    auto *quit_button = new QPushButton("Quit", this);

    layout->addWidget(edit_button);
    layout->addWidget(project_button);
    layout->addWidget(mod_button);
    layout->addWidget(run_button);
    layout->addWidget(quit_button);

    central_widget->setLayout(layout);
    setCentralWidget(central_widget);

    connect(edit_button, &QPushButton::clicked, this, &MainMenuWindow::on_edit_engine_content_clicked);
    connect(project_button, &QPushButton::clicked, this, &MainMenuWindow::on_create_edit_project_clicked);
    connect(mod_button, &QPushButton::clicked, this, &MainMenuWindow::on_mod_tools_clicked);
    connect(run_button, &QPushButton::clicked, this, &MainMenuWindow::on_run_project_clicked);
    connect(quit_button, &QPushButton::clicked, this, &MainMenuWindow::on_quit_clicked);
}

void MainMenuWindow::on_edit_engine_content_clicked() {
    std::cout << "Edit Engine Content Clicked" << std::endl;
    // In the future, this will open the EngineContentEditorWindow.
}

void MainMenuWindow::on_create_edit_project_clicked() {
    std::cout << "Create/Edit Project Clicked" << std::endl;
}

void MainMenuWindow::on_mod_tools_clicked() {
    std::cout << "Mod Tools Clicked" << std::endl;
}

void MainMenuWindow::on_run_project_clicked() {
    std::cout << "Run Game Clicked" << std::endl;
}

void MainMenuWindow::on_quit_clicked() {
    QApplication::quit();
}