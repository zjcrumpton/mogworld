#ifndef WINDOW_UTILS_HPP
#define WINDOW_UTILS_HPP

#include <QWidget>
#include <QScreen>
#include <QGuiApplication>

inline void center_on_parent(QWidget* child, QWidget* parent) {
    if (!parent) {
        QRect screen_geometry = QGuiApplication::primaryScreen()->geometry();
        child->move(screen_geometry.center() - child->rect().center());
        return;
    }

    QPoint parent_center = parent->geometry().center();
    QPoint child_top_left = parent_center - QPoint(child->width() / 2, child->height() / 2);
    child->move(child_top_left);
}

#endif
