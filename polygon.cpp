#include "shape.h"
#include<QtMath>

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
