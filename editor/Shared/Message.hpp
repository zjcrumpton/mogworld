#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <QMessageBox>
#include <iostream>

namespace Message {

void show_error(const std::string msg, QWidget* parent) {
    QMessageBox::critical(parent, "Error", QString::fromStdString(msg));
}

}

#endif // MESSAGE_HPP