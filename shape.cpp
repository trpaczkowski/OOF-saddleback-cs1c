#include "shape.h"
#include<QtMath>

/*************************************************************************

Shape Methods

**************************************************************************/

void Shape::setPen(Qt::GlobalColor color)

{
    QPainter::setPen(color);
}

void Shape::setPen(Qt::GlobalColor color, int width, Qt::PenStyle pen_style,
                   Qt::PenCapStyle cap_style, Qt::PenJoinStyle join_style)
{
    QPen pen;

    pen.setColor(color);

    pen.setWidth(width);

    pen.setStyle(pen_style);

    pen.setCapStyle((cap_style));

    pen.setJoinStyle(join_style);

    QPainter::setPen(pen);

}

void Shape::setBrush(Qt::GlobalColor color, Qt::BrushStyle brush_style)
{
    QBrush brush;

    brush.setColor(color);

    brush.setStyle(brush_style);

    QPainter::setBrush(brush);

}

void Shape::defaultStyle()
{

}
