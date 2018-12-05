#include "canvas.h"

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setFixedSize(sizeHint());
}

QSize Canvas::sizeHint() const
{
    return QSize(1000,500);
}

QSize Canvas::minimumSizeHint() const
{
    return QSize(1000,500);
}


void Canvas::paintEvent(QPaintEvent *)
{
    QPaintDevice* device = this;
    vector<Shape*>::iterator i = shapeList.begin();
    while(i < shapeList.end()) {
        (*i)->draw(device);
        ++i;
    }
}
