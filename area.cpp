
virtual double Polygon::area(const vector<QPointF> & points)
{
    double area;
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
virtual double Polygon::perimeter(const vector<QPointF> & points)
{
    double perimeter = 0;

    for(int i = 0; i < points.size()-1; i++)
    {
        perimeter += (qSqrt((points[i+1].x() - points[i.x()])^2 + (points[i+1].y() - points[i.y()])^2));
    }
    return perimeter;
}

virtual double Rectangle::area(const int & width, const int & height)
{
    return(width * height);
}
virtual double Rectangle::perimeter(const int & width, const int & height)
{
    return(2 * width + 2 * height);
}

virtual double Ellipse::area()
{
    return(width*height*M_PI);
}
virtual double Ellipse::perimeter(const int & minor, const int & major)
{
    return(M_PI(3(major + minor) - qSqrt((3*minor + major)(minor+3*major))));
}

virtual double Circle::area(const int & radius)
{
    return(radius * radius * M_PI);
}
virtual double Circle::perimeter(const int & radius)
{
    return(2 * M_PI * radius);
}
