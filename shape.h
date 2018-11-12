#ifndef SHAPE_H
#define SHAPE_H

#include <QApplication>
#include <QPainter>
#include "vector.h"

class Shape : public QPainter
{
    public:
    
        //ENUM - DEFINES SHAPE TYPE
        enum class ShapeType {NoShape, Line, Polyline, Polygon, Rectangle, Ellipse, Circle , Text};
        
        //CONSTRUCTOR
        Shape(QPaintDevice* device = nullptr, int id = -1, ShapeType shape = ShapeType::NoShape) :

              QPainter(device), shape_ID(id), shapeType(shape){}
              
        //VIRTUAL DECONSTRUCTOR
        virtual ~Shape() {}
              
        //FUNCTION - GETS SHAPE TYPE
        ShapeType getShape() const {return shapeType;}

        //FUNCTION - GETS SHAPE ID
        int getId() const {return shape_ID;}

        //FUNCTION - SETS SHAPE TYPE
        void setShape(ShapeType s) {shapeType = s;}
        
        //FUNCTION - SETS SHAPE ID
        void setId(int _id) {shape_ID = _id;}

        //FUNCTION - SETS PEN COLOR
        void setPen(Qt::GlobalColor color);

        //FUNCTION - SETS WIDTH, PEN STYLE, PEN CAP STYLE, AND PEN JOINT STYLE
        void setPen(Qt::GlobalColor, int width, Qt::PenStyle, Qt::PenCapStyle, Qt::PenJoinStyle);

        //FUNCTION - SETS BRUSH BRUSH STYLE
        void setBrush(Qt::GlobalColor, Qt::BrushStyle);

        //FUNCTION - SETS DEFAULT STYLE
        void defaultStyle();

        //VIRTUAL FUNCTION - DRAWS AND RENDERS SHAPE IN THE RENDERING AREA
        virtual void draw(const int x, const int y) = 0;
        
        //VIRTUAL FUNCTION - MOVES SHAPE TO COORDINATES
        virtual void move(const int x, const int y) = 0;
        
        //VIRTUAL FUNCTION - CALCULATES THE PERIMETER
        virtual double perimeter() = 0;
        
        //VIRTUAL FUNCTION - CALCULATES THE AREA
        virtual double area() = 0;
        
        //VIRTUAL FUNCTION - REMOVES THE SHAPE FROM THE RENDER SCREEN
        virtual void remove() = 0;

    private:
        
        int       shape_ID;   // Variable defines the shape ID
        ShapeType shapeType;  // Variable defines the shape type

};

#endif
