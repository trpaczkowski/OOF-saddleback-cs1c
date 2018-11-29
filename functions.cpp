#include <QFile>
#include "Shape.h"
#include "text.h"
#include <QTextStream>
#include <QMetaEnum>
#include <QPainter>

QString enumToString(Shape::ShapeType s);
Shape& readShape(QTextStream& in);
bool operator==(Shape::ShapeType& s1, Shape::ShapeType& s2);
/**
 * @brief Outputs the properties of the specified shape or text to external storage.
 * @param ShapeId the id
 * @param ShapeInfo the shape or text
 */
void save_shape_to_file(int ShapeId, Shape &s)
{
    QFile file("shapes.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

	
      out << "\nShapeId: " << ShapeId;
      out << "\nShapeType: " << enumToString(s.getShape());
    out << "\nShapeDimensions: " << "";
    if((s.getShape() == Shape::ShapeType::Line )|| (s.getShape() == Shape::ShapeType::Polyline) ||
            (s.getShape() == Shape::ShapeType::Rectangle)
        || (s.getShape() == Shape::ShapeType::Ellipse) || (s.getShape() == Shape::ShapeType::Circle))
    {
        out << "\nPenColor: " << s.pen().color().name();
        out << "\nPenWidth: " << s.pen().widthF();
        out << "\nPenStyle: " << s.pen().width();
        out << "\nPenCapStyle: " << s.pen().capStyle();
        out << "\nPenJoinStyle: " << s.pen().joinStyle();
        if((s.getShape() == Shape::ShapeType::Rectangle) ||
                (s.getShape() == Shape::ShapeType::Ellipse) || (s.getShape() == Shape::ShapeType::Circle))
        {
            out << "\nBrushColor: " << s.brush().style();
            out << "\nBrushStyle: " << s.brush().style();
        }
    }
    else //if the shape is text
    {
        Text& t = dynamic_cast<Text&>(s);
        out << "\nTextString: " << t.getTextString();
        out << "\nTextColor: " << t.pen().color().name();
        out << "\nTextAlignment: " << t.getAlignment();
        out << "\nTextPointSize: " << t.fontInfo().pointSize();
        out << "\nTextFontFamily: " << t.fontInfo().family();
        out << "\nTextFontStyle: " << t.fontInfo().style();
        out << "\nTextFontWeight: " << t.fontInfo().weight();
    }	
    file.close();
}

bool operator==(Shape::ShapeType& s1, Shape::ShapeType& s2)
{
    return enumToString(s1) == enumToString(s2);
}

/**
 * @brief converts a shapetype enum to a string
 * @param s
 * @return
 */
QString enumToString(Shape::ShapeType s)
{
    switch (s)
    {
    case Shape::ShapeType::Line: return "Line";
    case Shape::ShapeType::Polyline: return "Polyline";
    case Shape::ShapeType::Polygon: return "Polygon";
    case Shape::ShapeType::Rectangle: return "Rectangle";
    case Shape::ShapeType::Ellipse: return "Ellipse";
    case Shape::ShapeType::Circle: return "Circle";
    default: return "Not A Shape";
    }
}
