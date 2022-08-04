#ifndef BOX_H
#define BOX_H

#include <QMainWindow>
#include <QPushButton>

class Box : public QPushButton {
public:
    Box(const QString& text, QWidget* parent = nullptr);

public slots:

        void onClick();
};

#endif // BOX_H
