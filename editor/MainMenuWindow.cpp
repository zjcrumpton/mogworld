#include "MainMenuWindow.hpp"
#include <QVBoxLayout>
#include <QPushButton>
#include <QApplication>
#include <QLabel>
#include <iostream>

MainMenuWindow::MainMenuWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Mogworld Engine - Main Menu");

    resize(600, 400);

    auto *central_widget = new QWidget(this);
    auto *layout = new QVBoxLayout();

    auto *title_label = new QLabel("MogWorld Engine", this);
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setStyleSheet("font-size: 40px; font-weight: bold;");

    auto *edit_button = new QPushButton("Edit Engine Content", this);
    auto *project_button = new QPushButton("Create or Edit a Game Project", this);
    auto *mod_button = new QPushButton("Mod Tools", this);
    auto *run_button = new QPushButton("Run Game Project", this);
    auto *quit_button = new QPushButton("Quit", this);

    QString button_style = "font-size: 18px; padding: 10px;";
    edit_button->setStyleSheet(button_style);
    project_button->setStyleSheet(button_style);
    mod_button->setStyleSheet(button_style);
    run_button->setStyleSheet(button_style);
    quit_button->setStyleSheet(button_style);

    layout->addWidget(title_label);
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