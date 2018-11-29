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

/*************************************************************************

Line Methods

**************************************************************************/

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

/*************************************************************************

Polyline Methods

**************************************************************************/

void Polyline::addPoint(const QPointF &point)
{
    points.push_back(point);

}

void Polyline::draw(const int x, const int y)
{
    QPointF line_points[points.size()];

    for (int i = 0; i < points.size(); i++)
    {
        line_points[i] = points[i];
    }

    save();

    translate(x,y);

    drawPolyline(line_points, points.size());

    restore();

}

void Polyline::move(const int x, const int y)
{
    QPointF line_points[points.size()];

    for (int i = 0; i < points.size(); i++)
    {
        line_points[i] = points[i];
    }

    save();

    remove();

    translate(x,y);

    drawPolyline(line_points, points.size());

    restore();

}

void Polyline::remove()
{
    //we have to craft a rectangle that will enclose only this shape and delete it

    save();

    QPointF topPoint(0,0);

    QPointF leftPoint(0,0);

    QPointF rightPoint(0,0);

    QPointF bottomPoint(0,0);

    for (int i = 0; i < points.size(); i++)
    {
        //grab the highest point

       if (points[i].y() <= topPoint.y())
       {
           topPoint = points[i];
       }

       //grab the rightmost point

       if (points[i].x() >= rightPoint.x())
       {
           rightPoint = points[i];
       }

       //grab the leftmost point

       if (points[i].x() <= leftPoint.x())
       {
           leftPoint = points[i];
       }

       //grab the bottom point

       if (points[i].y() >= bottomPoint.y())
       {
           bottomPoint = points[i];
       }

    }

    double width = rightPoint.x() - leftPoint.x();

    double height = bottomPoint.y() - topPoint.y();

    QRect rect((int)leftPoint.x(), (int)topPoint.y(), width, height);

    eraseRect(rect);

    restore();

}

/*************************************************************************

Polygon Methods

**************************************************************************/

void Polygon::addPoint(const QPointF &point)
{
    points.push_back(point);
}

void Polygon::draw(const int x, const int y)
{
    QPointF line_points[points.size()];

    for (int i = 0; i < points.size(); i++)
    {
        line_points[i] = points[i];
    }

    save();

    translate(x,y);

    drawPolygon(line_points, points.size());

    restore();

}

double Polygon::area()
{
    double area = 0;

    for(int i = 0; i < points.size(); i++)
    {
        if(i == points.size()-1)
        {
            area += points[i].x() * points[0].y();

            area -= points[i].y() * points[0].x();

        }
        else
        {
            area += points[i].x() * points[i+1].y();

            area -= points[i].y() * points[i+1].x();

        }

    }
    return (qAbs(area) / 2);

}

double Polygon::perimeter()
{
    double perimeter = 0;

    for(int i = 0; i < points.size()-1; i++)
    {
        perimeter += (qSqrt((points[i+1].x() - points[i].x()) * (points[i+1].x() - points[i].x())

                + (points[i+1].y() - points[i].y()) * (points[i+1].y() - points[i].y())));

    }
    return perimeter;

}

void Polygon::move(const int x, const int y)
{
    save();

    remove();

    translate(x,y);

    QPointF line_points[points.size()];

    for (int i = 0; i < points.size(); i++)
    {
        line_points[i] = points[i];

    }

    drawPolygon(line_points, points.size());

    restore();

}

void Polygon::remove()
{
    //we have to craft a rectangle that will enclose only this shape and delete it

    save();

    QPointF topPoint(0,0);

    QPointF leftPoint(0,0);

    QPointF rightPoint(0,0);

    QPointF bottomPoint(0,0);

    for (int i = 0; i < points.size(); i++)
    {
        //grab the highest point
       if (points[i].y() <= topPoint.y())
       {
           topPoint = points[i];
       }

       //grab the rightmost point
       if (points[i].x() >= rightPoint.x())
       {
           rightPoint = points[i];
       }

       //grab the leftmost point
       if (points[i].x() <= leftPoint.x())
       {
           leftPoint = points[i];
       }

       //grab the bottom point
       if (points[i].y() >= bottomPoint.y())
       {
           bottomPoint = points[i];
       }

    }

    double width = rightPoint.x() - leftPoint.x();

    double height = bottomPoint.y() - topPoint.y();

    QRect rect((int)leftPoint.x(), (int)topPoint.y(), width, height);

    eraseRect(rect);

    restore();

}

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
