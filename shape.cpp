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


void Line::move(const int x, const int y, int coordNum)
{
    QPoint tempPoint(x, y);
    switch(coordNum)
    {
    //Change first coordinate
    case 1:{begin = tempPoint;}
        break;
    //Change second coordinate
    case 2:{end = tempPoint;}
        break;
    //Did not choose correct Coordinate Number
    default: {}
    }

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

void Polyline::move(const int x, const int y, int coordNum)
{
    QPoint tempPoint(x, y);
    switch(coordNum)
    {
    //Change first coordinate
    case 1:{points[0] = tempPoint;}
        break;
    //Change second coordinate
    case 2:{points[1] = tempPoint;}
        break;
    //Change third coordinate
    case 3:{points[2] = tempPoint;}
        break;
    //Change fourth coordinate
    case 4:{points[3] = tempPoint;}
        break;
    //Change fifth coordinate
    case 5:{points[4] = tempPoint;}
        break;
    //Change sixth coordinate
    case 6:{points[5] = tempPoint;}
        break;
    //Did not choose correct Coordinate Number
    default: {}
    }

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

void Polygon::move(const int x, const int y, int coordNum)
{
    QPoint tempPoint(x, y);
    switch(coordNum)
    {
    //Change first coordinate
    case 1:{points[0] = tempPoint;}
        break;
    //Change second coordinate
    case 2:{points[1] = tempPoint;}
        break;
    //Change third coordinate
    case 3:{points[2] = tempPoint;}
        break;
    //Change fourth coordinate
    case 4:{points[3] = tempPoint;}
        break;
    //Change fifth coordinate
    case 5:{points[4] = tempPoint;}
        break;
    //Change sixth coordinate
    case 6:{points[5] = tempPoint;}
        break;
    //Change seventh coordinate
    case 7:{points[6] = tempPoint;}
        break;
    //Change eigth coordinate
    case 8:{points[7] = tempPoint;}
        break;
    //Did not choose correct Coordinate Number
    default: {}
    }

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

void Rectangle::move(const int x, const int y, int coordNum)
{
    QPoint tempPoint(x, y);
    position = tempPoint;
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

void Ellipse::move(const int x, const int y, int coordNum)
{
    QPoint tempPoint(x, y);
    position = tempPoint;

}



double Text::area()
{
    return double(width * height);
}

vector<QString> Text::dimensionLabels()
{
    vector<QString> ret;
    ret.push_back("Position:");
    ret.push_back("(" + QString::number(position.x()) + ", " + QString::number(position.y()) + ")");
    ret.push_back("Width:");
    ret.push_back(QString::number(width));
    ret.push_back("Height:");
    ret.push_back(QString::number(height));

    return ret;
}

void Text::draw(const int x, const int y)
{
    save();

    translate(x,y);

    painter.drawText(position.x(), position.y(), width, height, alignmentFlags, text);

    restore();
}

vector<int> Text::getDimensions()
{
    vector<int> dimension;
    dimension.push_back(position.x());
    dimension.push_back(position.y());
    dimension.push_back(width);
    dimension.push_back(height);

    return dimension;
}

QFont& Text::getFont()
{
    return font;
}

Qt::AlignmentFlag Text::getAlignment() const
{
    return alignmentFlags;
}

QString Text::getText() const
{
    return text;
}

void Text::move(const int x, const int y, int coordNum)
{
    QPoint tempPoint(x, y);
    position = tempPoint;
}

double Text::perimeter()
{
    return 2.0 * (width + height);
}

void Text::setAlignment(Qt::AlignmentFlag flags)
{
    alignmentFlags = flags;
}

void Text::setDimensions(int w, int h)
{
    width = w;
    height = h;
}

void Text::setFont(bool boldIn, bool italicIn, int pointSizeIn, int weightIn)
{
    font.setBold(boldIn);
    font.setItalic(italicIn);
    font.setPointSize(pointSizeIn);
    font.setWeight(weightIn);
}

void Text::setPosition(int x, int y)
{
    position = { x, y };
}

void Text::setText(const QString& textIn)
{
    text = textIn;
}

