
#include "shape.h"
#include <QtMath>

/*************************************************************************
Circle Methods
**************************************************************************/

void Circle::draw(const int x, const int y)
{
    save();

    translate(x,y);

    drawEllipse(position, radius, radius);

    restore();

}

double Circle::area()
{
    return(radius * radius * M_PI);

}

double Circle::perimeter()
{
    return(2 * M_PI * radius);

}

void Circle::move(const int x, const int y)
{
    save();

    remove();

    translate(x,y);

    drawEllipse(x, y, radius, radius);

    restore();

}

void Circle::remove()
{
    save();

    QRect rect(position.x(), position.y(), radius, radius);

    eraseRect(rect);

    restore();

}

void Circle::setDimensions(double radius)
{
    this->radius = radius;

}
