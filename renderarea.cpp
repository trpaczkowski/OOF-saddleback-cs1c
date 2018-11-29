#include "renderarea.h"
#include <unistd.h>
#include <iostream>
#include <QTextStream>
#include <QPainter>
#include <QFile>
#include "text.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    move_id = -1; //default, no move operations
    remove_id = -1; //default, nothing to remove

}

RenderArea::~RenderArea()
{
    for (int i = 0; i < shapes.size(); i++)
    {
        delete shapes[i];
    }
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

int RenderArea::getShapeIndexById(int id)
{
    for (int i = 0; i < shapes.size(); i++)
    {
        if (shapes[i]->getId() == id)
        {
            return i;
        }
    }
    return -1;
}

/**
 * @brief creates a new unique id for the newly added shape.
 * The id is made unique by finding the largest id in the current
 * shape vector and returning that id + 1.
 * @return
 */
int RenderArea::getNewId()
{
    int id = shapes[0]->getId();
    for (int i = 0; i < shapes.size(); i++)
    {
        if (id > shapes[i]->getId())
        {
            id = shapes[i]->getId();
        }
    }
    return (id + 1);
}

/**
 * @brief The fruit of Kevin's genius: the paintevent function is overridden
 * to handle any and all shape events, including move/remove, update, and add.
 * It works by firstly rendering all shapes currently in the vector.
 * It then handles any move operations, which are queued up by setting the move_id value.
 * The same is then repeated for the remove_id.
 */
void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    //render all shapes currently stored
    for (int i = 0; i < shapes.size(); i++)
    {
        shapes[i]->draw(0,0);
    }

    //handle any move operation
    if (move_id != -1)
    {
        Shape* shapeToMove;
        for (int i = 0; i < shapes.size(); i++)
        {
            if (shapes[i]->getId() == move_id)
            {
                shapeToMove = shapes[i];
            }
        }
        shapeToMove->move(x_move_coord, y_move_coord);
        move_id = -1; //move finished, reset id
    }
    //handle any remove operation
    if (remove_id != -1)
    {
        int index = getShapeIndexById(remove_id);
        if (index != -1)
        {
            shapes[index]->remove();
            shapes.erase(shapes.begin() + index);
            remove_id = -1; //reset id
        }

    }    
}

/**
 * @brief returns a Qt enum corresponding to the specified color string.
 * @param line
 * @return
 */
Qt::GlobalColor string_to_color(QString line)
{
    line = line.toLower();
    if(line == "blue"){return Qt::blue;}
    else if(line == "red"){return Qt::red;}
    else if(line == "cyan"){return Qt::cyan;}
    else if(line == "yellow"){return Qt::yellow;}
    else if(line == "magenta"){return Qt::magenta;}
    else if(line == "black"){return Qt::black;}
    else if(line == "green"){return Qt::green;}
}

/**
 * @brief Returns a Qt enum corresponding to the specified pen style.
 * @param line
 * @return
 */
Qt::PenStyle string_to_penstyle(QString line)
{
    if(line == "DashDotLine"){return Qt::DashDotLine;}
    else if(line == "SolidLine"){return Qt::SolidLine;}
    else if(line == "DashLine"){return Qt::DashLine;}
    else if(line == "DotLine"){return Qt::DotLine;}
    else if(line == "CustomDashLine"){return Qt::CustomDashLine;}
    else if(line == "DashDotDotLine"){return Qt::DashDotDotLine;}
}

/**
 * @brief Returns a Qt enum corresponding to the specified cap style.
 * @param line
 * @return
 */
Qt::PenCapStyle string_to_capstyle(QString line)
{
    if(line == "SquareCap"){return Qt::SquareCap;}
    else if(line == "RoundCap"){return Qt::RoundCap;}
    else if(line == "FlatCap"){return Qt::FlatCap;}
}

/**
 * @brief Returns a Qt enum corresponding to the specified join style.
 * @param line
 * @return
 */
Qt::PenJoinStyle string_to_joinstyle(QString line)
{
    if(line == "MiterJoin"){return Qt::MiterJoin;}
    else if(line == "RoundJoin"){return Qt::RoundJoin;}
    else if(line == "BevelJoin"){return Qt::BevelJoin;}
}

/**
 * @brief Returns a Qt enum corresponding to the specified brush style.
 * @param line
 * @return
 */
Qt::BrushStyle string_to_brushstyle(QString line)
{
   if(line == "SolidPattern"){return Qt::SolidPattern;}
   else if(line == "VerPattern"){return Qt::VerPattern;}
   else if(line == "HorPattern"){return Qt::HorPattern;}
}

/**
 * @brief Returns a Qt enum corresponding to the specified text style.
 * @param line
 * @return
 */
QFont::Style string_to_textstyle(QString line)
{
    if(line == "StyleNormal")
    {
        return QFont::StyleNormal;
    }
    else if(line == "StyleItalic")
    {
        return QFont::StyleItalic;
    }
    else if(line == "StyleOblique")
    {
        return QFont::StyleOblique;
    }
}

/**
 * @brief Reads and returns a single Shape from the file.
 * @param shape_text_stream
 * @return
 */
Shape * RenderArea::get_shape(QTextStream& shape_text_stream)
{
    Shape * shape;

    QString line = shape_text_stream.readLine();
    int shape_id = line.split(" ")[1].toInt();

    line = shape_text_stream.readLine();
    QString shape_type = line.split(" ")[1];

    if(shape_type == "Line")
    {
        // make line object
        shape = new Line(this,shape_id);

        // assign points
        line = shape_text_stream.readLine();
        line = line.replace(",","");
        QStringList list = line.split(" ");

        QPoint p1(list[1].toInt() , list[2].toInt());
        QPoint p2(list[3].toInt() , list[4].toInt());

        dynamic_cast<Line*>(shape)->setPoints(p1,p2);

        // assign pen
        line = shape_text_stream.readLine();
        Qt::GlobalColor color = string_to_color(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        int width = line.split(" ")[1].toInt();
        line = shape_text_stream.readLine();
        Qt::PenStyle style = string_to_penstyle(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        Qt::PenCapStyle capstyle = string_to_capstyle(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        Qt::PenJoinStyle joinstyle = string_to_joinstyle(line.split(" ")[1]);
        shape->setPen(color, width, style, capstyle, joinstyle);

        return shape;
    }
    else if(shape_type == "Polyline")
    {
        // make polyline object
        shape = new Polyline(this,shape_id);

        // assign points
        line = shape_text_stream.readLine();
        line = line.replace(",", "");
        QStringList list = line.split(" ");

        QPoint p1(list[1].toInt() , list[2].toInt());
        QPoint p2(list[3].toInt() , list[4].toInt());
        QPoint p3(list[5].toInt() , list[6].toInt());
        QPoint p4(list[7].toInt() , list[8].toInt());

        dynamic_cast<Polyline*>(shape)->addPoint(p1);
        dynamic_cast<Polyline*>(shape)->addPoint(p2);
        dynamic_cast<Polyline*>(shape)->addPoint(p3);
        dynamic_cast<Polyline*>(shape)->addPoint(p4);


        // assign pen
        line = shape_text_stream.readLine();
        Qt::GlobalColor color = string_to_color(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        int width = line.split(" ")[1].toInt();
        line = shape_text_stream.readLine();
        Qt::PenStyle style = string_to_penstyle(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        Qt::PenCapStyle capstyle = string_to_capstyle(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        Qt::PenJoinStyle joinstyle = string_to_joinstyle(line.split(" ")[1]);
        shape->setPen(color, width, style, capstyle, joinstyle);

        return shape;
    }
    else if(shape_type == "Polygon")
    {
        shape = new Polygon(this,shape_id);

        // assign points
        line = shape_text_stream.readLine();
        line = line.replace(",", "");
        QStringList list = line.split(" ");

        QPoint p1(list[1].toInt() , list[2].toInt());
        QPoint p2(list[3].toInt() , list[4].toInt());
        QPoint p3(list[5].toInt() , list[6].toInt());
        QPoint p4(list[7].toInt() , list[8].toInt());

        dynamic_cast<Polygon*>(shape)->addPoint(p1);
        dynamic_cast<Polygon*>(shape)->addPoint(p2);
        dynamic_cast<Polygon*>(shape)->addPoint(p3);
        dynamic_cast<Polygon*>(shape)->addPoint(p4);

        // assign pen
        line = shape_text_stream.readLine();
        Qt::GlobalColor color = string_to_color(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        int width = line.split(" ")[1].toInt();
        line = shape_text_stream.readLine();
        Qt::PenStyle style = string_to_penstyle(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        Qt::PenCapStyle capstyle = string_to_capstyle(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        Qt::PenJoinStyle joinstyle = string_to_joinstyle(line.split(" ")[1]);
        shape->setPen(color, width, style, capstyle, joinstyle);

        // assign brush
        line = shape_text_stream.readLine();
        color = string_to_color(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        Qt::BrushStyle brushstyle = string_to_brushstyle(line.split(" ")[1]);
        shape->setBrush(color, brushstyle);

        return shape;
    }
    else if(shape_type == "Rectangle")
    {
        shape = new Rectangle(this,shape_id);

        // assign points
        line = shape_text_stream.readLine();
        line = line.replace(",", "");
        QStringList list = line.split(" ");



        //dynamic_cast<Rectangle*>(shape)->setDimensions();

        // assign pen
        line = shape_text_stream.readLine();
        Qt::GlobalColor color = string_to_color(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        int width = line.split(" ")[1].toInt();
        line = shape_text_stream.readLine();
        Qt::PenStyle style = string_to_penstyle(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        Qt::PenCapStyle capstyle = string_to_capstyle(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        Qt::PenJoinStyle joinstyle = string_to_joinstyle(line.split(" ")[1]);
        shape->setPen(color, width, style, capstyle, joinstyle);

        // assign brush
        line = shape_text_stream.readLine();
        color = string_to_color(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        Qt::BrushStyle brushstyle = string_to_brushstyle(line.split(" ")[1]);
        shape->setBrush(color, brushstyle);

        return shape;
    }
    else if(shape_type == "Ellipse")
    {
        // assign points
                line = shape_text_stream.readLine();
                line = line.replace(",", "");
                QStringList list = line.split(" ");
                QPoint point(list[1].toInt(),list[2].toInt());

                dynamic_cast<Ellipse*>(shape)->setPosition(point);
                dynamic_cast<Ellipse*>(shape)->setDimensions(list[3].toInt(),list[4].toInt());

                // assign pen
                line = shape_text_stream.readLine();
                Qt::GlobalColor color = string_to_color(line.split(" ")[1]);
                line = shape_text_stream.readLine();
                int width = line.split(" ")[1].toInt();
                line = shape_text_stream.readLine();
                Qt::PenStyle style = string_to_penstyle(line.split(" ")[1]);
                line = shape_text_stream.readLine();
                Qt::PenCapStyle capstyle = string_to_capstyle(line.split(" ")[1]);
                line = shape_text_stream.readLine();
                Qt::PenJoinStyle joinstyle = string_to_joinstyle(line.split(" ")[1]);
                shape->setPen(color, width, style, capstyle, joinstyle);

                // assign brush
                line = shape_text_stream.readLine();
                color = string_to_color(line.split(" ")[1]);
                line = shape_text_stream.readLine();
                Qt::BrushStyle brushstyle = string_to_brushstyle(line.split(" ")[1]);
                shape->setBrush(color, brushstyle);

                shape_text_stream.readLine();
                return shape;


    }
    else if(shape_type == "Circle")
    {
        shape = new Circle(this,shape_id);
        // assign points
        line = shape_text_stream.readLine();
        line = line.replace(",", "");
        QStringList list = line.split(" ");
        QPoint point(list[1].toInt(),list[2].toInt());

        dynamic_cast<Circle*>(shape)->setPosition(point);
        dynamic_cast<Circle*>(shape)->setDimensions(list[3].toInt());

        // assign pen
        line = shape_text_stream.readLine();
        Qt::GlobalColor color = string_to_color(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        int width = line.split(" ")[1].toInt();
        line = shape_text_stream.readLine();
        Qt::PenStyle style = string_to_penstyle(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        Qt::PenCapStyle capstyle = string_to_capstyle(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        Qt::PenJoinStyle joinstyle = string_to_joinstyle(line.split(" ")[1]);
        shape->setPen(color, width, style, capstyle, joinstyle);

        // assign brush
        line = shape_text_stream.readLine();
        color = string_to_color(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        Qt::BrushStyle brushstyle = string_to_brushstyle(line.split(" ")[1]);
        shape->setBrush(color, brushstyle);

        shape_text_stream.readLine();
        return shape;
    }
    else if(shape_type == "Text")
    {
        shape = new Text(this,shape_id);

        // assign points
        line = shape_text_stream.readLine();
        line = line.replace(",", "");
        QStringList list = line.split(" ");
        QPointF point(list[1].toInt() , list[2].toInt());

        dynamic_cast<Text*>(shape)->setPosition(point);
        dynamic_cast<Text*>(shape)->setDimensions(list[3].toInt(),list[4].toInt());

        // assign text options
        QFont font;
        line = shape_text_stream.readLine();
        dynamic_cast<Text*>(shape)->setTextString(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        Qt::GlobalColor color = string_to_color(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        dynamic_cast<Text*>(shape)->setAlignment(line.split(" ")[1]);
        line = shape_text_stream.readLine();
        font.setPointSize(line.split(" ")[1].toInt());
        line = shape_text_stream.readLine();
        font.setFamily("Comic Sans MS");
        line = shape_text_stream.readLine();
        font.setStyle(string_to_textstyle(line.split(" ")[1]));
        line = shape_text_stream.readLine();
        font.setWeight(line.split(" ")[1].toInt());
        shape->setPen(color);

        shape_text_stream.readLine();
        return shape;
    }
}

/**
 * @brief Fills the shapes vector with shapes from the file.
 * @param filename
 * @param shapes
 */
void RenderArea::populate_shapes(QString& filename, vector<Shape*> & shapes)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream shape_text_stream(&file);

    shape_text_stream.readLine();

    while(shape_text_stream.atEnd() == false)
    {
        shapes.push_back(get_shape(shape_text_stream));
    }

    file.close();
}
