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
   // for(vector<Shape*>::iterator it = shapeList->begin(); it != shapeVector->end(); ++it)
//    QPaintDevice* device = this;

//    VecSTD::vector<Shape*>::iterator i = shapeList.begin();
//    while(i < shapeList.end()) {
//        (*i)->draw();
//        ++i;
//    }
    //shapeList[0]->draw();

//    QPainter painter(this);
//        Shapes::Rectangle  rect(&painter, 20, 20, 1, 100, 200);
//        QColor c("red");
        //painter.setPen(c);
        //painter.drawRect(QRectF(20, 20, 100, 200));
//        rect.setPenColor(c);
//        rect.setPenStyle(Qt::SolidLine);
//        rect.draw();

    //shapeList[0]->draw();

//    int index =0;
//    while(index < shapeList.size())
//    {
//        shapeList[index]->draw();
//            index++;
//    }

    QPaintDevice* device = this;
    vector<Line*>::iterator i = shapeList.begin();
    while(i < shapeList.end()) {
        (*i)->draw(device);
        ++i;
    }
}
