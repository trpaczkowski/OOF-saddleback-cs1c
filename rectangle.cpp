#include "shape.h"
#include <QtMath>

/*************************************************************************
Rectangle Methods
**************************************************************************/

void Rectangle::setDimensions(int width, int height)
{
    this->width = width;

    this->height = height;

}

void Rectangle::draw(const int x, const int y)
{
    save();

    translate(x,y);

    drawRect(position.x(), position.y(), width, height);

    restore();

}

double Rectangle::area()
{

    return(width * height);

}

double Rectangle::perimeter()
{

    return(2 * width + 2 * height);

}

void Rectangle::move(const int x, const int y)
{
    save();

    remove();

    translate(x,y);

    drawRect(x, y, width, height);

    restore();

}

void Rectangle::remove()
{
    save();

    QRect rect(position.x(), position.y(), width, height);

    eraseRect(rect);

    restore();

}
