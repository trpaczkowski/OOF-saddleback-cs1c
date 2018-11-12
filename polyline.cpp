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
