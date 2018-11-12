#include "shape.h"
#include<QtMath>

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
