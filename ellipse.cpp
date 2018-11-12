#include "shape.h"
#include <QtMath>

/*************************************************************************
Ellipse Methods
**************************************************************************/

void Ellipse::draw(const int x, const int y)
{
    save();

    translate(x,y);

    drawEllipse(position, width, height);

    restore();

}

double Ellipse::area()
{
    return(width * height * M_PI);

}

double Ellipse::perimeter()

{
    return(M_PI * 3 * (width + height) - qSqrt((3 * width + height) * (width + 3 * height)));

}

void Ellipse::move(const int x, const int y)
{
    save();

    remove();

    translate(x,y);

    drawEllipse(x, y, width, height);

    restore();

}

void Ellipse::remove()
{
    save();

    QRect rect(position.x(), position.y(), width, height);

    eraseRect(rect);

    restore();

}
