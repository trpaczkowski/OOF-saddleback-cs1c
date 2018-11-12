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

class Line : public Shape
{
    public:
    
        //CONSTRUCTOR
        Line(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::Line) {}
        
        //DECONSTRUCTOR
        ~Line() override {}
        
        //FUNCTION - SETS BEGINNING AND ENDING POINTS
        void setPoints(const QPoint& begin, const QPoint& end);
        
        //FUNCTION - DRAWS AND RENDERS SHAPE IN THE RENDERING AREA
        void draw(const int x, const int y)  override;
        
        //FUNCTION - MOVES SHAPE TO COORDINATES
        void move(const int x, const int y) override;
        
        //FUNCTION - REMOVES THE SHAPE FROM THE RENDER SCREEN
        void remove() override;
        
        //FUNCTION - CALCULATES THE PERIMETER
        double perimeter() override {return 0;}
        
        //FUNCTION - CALCULATES THE AREA
        double area() override {return 0;}

        //FUNCTION - GETS BEGINNING POINT
        QPoint& getBeginPoint() { return begin;}
        
        //FUNCTION - GETS ENDING POINT
        QPoint& getEndPoint() {return end;}

    private:
    
        QPoint begin;  // Variable defines the beginning point
        QPoint end;    // Variable defines the ending point

};

class Polyline : public Shape
{
    public:
        
        //CONSTRUCTOR
        Polyline(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::Polyline) {}
        
        //DECONSTRUCTOR
        ~Polyline()  override {}
        
        //FUNCTION - ADDS A POINT
        void addPoint(const QPointF& point);
        
        //FUNCTION - DRAWS AND RENDERS SHAPE IN THE RENDERING AREA
        void draw(const int x, const int y)  override;
        
        //FUNCTION - MOVES SHAPE TO COORDINATES
        void move(const int x, const int y) override;
        
        //FUNCTION - REMOVES THE SHAPE FROM THE RENDER SCREEN
        void remove() override;
        
        //FUNCTION - CALCULATES THE PERIMETER
        double perimeter() override {return 0;}
        
        //FUNCTION - CALCULATES THE AREA
        double area() override {return 0;}
        
        //FUNCTION - GETS SHAPE POINTS
        vector<QPointF>& getPoints() {return points;}

    private:
    
        vector<QPointF> points;  // Vector Variable defines shape points

};

class Polygon : public Shape
{
    public:
    
        //CONSTRUCTOR
        Polygon(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::Polygon) {}
        
        //DECONSTRUCTOR
        ~Polygon() override {}
        
        //FUNCTION - ADDS SHAPE POINTS
        void addPoint(const QPointF& point);
        
        //FUNCTION - DRAWS AND RENDERS SHAPE IN THE RENDERING AREA
        void draw(const int x, const int y)  override;
        
        //FUNCTION - MOVES SHAPE TO COORDINATES
        void move(const int x, const int y) override;

        //FUNCTION - REMOVES THE SHAPE FROM THE RENDER SCREEN
        void remove() override;

        //FUNCTION - CALCULATES THE PERIMETER
        double perimeter() override;
        
        //FUNCTION - CALCULATES THE AREA
        double area() override;
        
        //FUNCTION - GETS SHAPE POINTS
        vector<QPointF>& getPoints() { return points;}

    private:
    
        vector<QPointF> points;  // Vector Variable defines shape points

};

class Rectangle : public Shape
{
    public:
    
        //CONSTRUCTOR
        Rectangle(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::Rectangle) {}
        
        //DECONSTRUCTOR
        ~Rectangle() override {}
        
        //FUNCTION - SETS POSITION
        void setPosition(const QPoint& point) {position = point;}
        
        //FUNCTION - SETS SHAPE DIMENSIONS
        void setDimensions(int width, int height);
        
        //FUNCTION - DRAWS AND RENDERS SHAPE IN THE RENDERING AREA
        void draw(const int x, const int y)  override;

        //FUNCTION - CALCULATES THE PERIMETER
        double perimeter() override;
        
        //FUNCTION - CALCULATES THE AREA
        double area() override;

        //FUNCTION - MOVES SHAPE TO COORDINATES
        void move(const int x, const int y) override;
        
        //FUNCTION - REMOVES THE SHAPE FROM THE RENDER SCREEN
        void remove() override;

        //FUNCTION - GETS POSITION
        QPoint& getPosition() {return position;}
        
        //FUNCTION - GETS WIDTH
        int getWidth() {return width;}
        
        //FUNCTION - GETS HEIGHT
        int getHeight() {return height;}

    private:
    
        QPoint position;  // Variable defines the shapes position
        int    width;     // Variable defines shape width
        int    height;    // Variable defines shape height

};

class Ellipse : public Shape
{
    public:
    
        //CONSTRUCTOR
        Ellipse(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::Ellipse) {}
        
        //DECONSTRUCTOR
        ~Ellipse() override {}
        
        //FUNCTION - SETS POSITION
        void setPosition(const QPointF& point) {position = point;}
        
        //FUNCTION - SETS SHAPE DIMENSIONS
        void setDimensions(float width, float height) {this->width = width; this->height = height;}

        //FUNCTION - DRAWS AND RENDERS SHAPE IN THE RENDERING AREA
        void draw(const int x, const int y)  override;

        //FUNCTION - CALCULATES THE PERIMETER
        double perimeter() override;
        
        //FUNCTION - CALCULATES THE AREA
        double area() override;
        
        //FUNCTION - MOVES SHAPE TO COORDINATES
        void move(const int x, const int y) override;
        
        //FUNCTION - REMOVES THE SHAPE FROM THE RENDER SCREEN
        void remove() override;
        
        //FUNCTION - GETS SHAPE POSITION
        QPointF& getPosition() {return position;}

        //FUNCTION - GETS WIDTH
        double getWidth() {return width;}
        
        //FUNCTION - GETS HEIGHT
        double getHeight() {return height;}

    private:
    
        QPointF position;  // Variable defines the shapes position
        double  width;     // Variable defines shape width
        double  height;    // Variable defines shape height

};

class Circle : public Shape
{
    public:
    
        //CONSTRUCTOR
        Circle(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::Circle) {}
        
        //DECONSTRUCTOR
        ~Circle() override {}
        
        //FUNCTION - SETS POSITION
        void setPosition(const QPointF& point) {position = point;}

        void setRadius(double radius) {this->radius = radius;}
        
        //FUNCTION - SETS SHAPE DIMENSIONS
        void setDimensions(double radius);
        
        //FUNCTION - DRAWS AND RENDERS SHAPE IN THE RENDERING AREA
        void draw(const int x, const int y)  override;

        //FUNCTION - CALCULATES THE PERIMETER
        double perimeter() override;
        
        //FUNCTION - CALCULATES THE AREA
        double area() override;
        
        //FUNCTION - MOVES SHAPE TO COORDINATES
        void move(const int x, const int y) override;
        
        //FUNCTION - REMOVES THE SHAPE FROM THE RENDER SCREEN
        void remove() override;
        
        //FUNCTION - GETS SHAPE POSITION
        QPointF& getPosition() {return position;}
        
        //FUNCTION - GETS SHAPE RADIUS
        double getRadius() {return radius;}

    private:
    
        QPointF position;  // Variable defines the shapes position
        double  radius;    // Variable defines the shapes radius

};

#endif // SHAPE_H
