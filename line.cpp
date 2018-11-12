#include "shape.h"
#include <QtMath>

/****************
 * Line Methods *
 ****************/

void Line::setPoints(const QPoint &begin, const QPoint &end)
{
    this->begin = begin;

    this->end = end;

}

void Line::draw(const int x, const int y)
{
    save();

    translate(x,y);

    drawLine(begin, end);

    restore();

}

void Line::move(const int x, const int y)
{
    save();

    remove();

    translate(x,y);

    drawLine(begin, end);

    restore();

}

void Line::remove()
{
    save();

    QRect rect(begin, end);

    eraseRect(rect);

    restore();

}
