//box.cpp
#include "box.h"

Box::Box(const QString& text, QWidget* parent)
    : QPushButton(text, parent)
{
    connect(this, &QPushButton::clicked,this, &Box::onClick);
}

void Box::onClick()
{
    qDebug() << "test";
}
