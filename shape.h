#ifndef SHAPE_H
#define SHAPE_H

#include <QApplication>
#include <QPainter>
#include "vector.h"

//HELLo

class Shape : public QPainter
{
    public:

        enum class ShapeType {NoShape, Line, Polyline, Polygon, Rectangle, Ellipse, Circle , Text};

        ShapeType getShape() const {return shapeType;}

        int getId() const {return shape_ID;}

        Shape(QPaintDevice* device = nullptr, int id = -1, ShapeType shape = ShapeType::NoShape) :

             QPainter(device), shape_ID(id), shapeType(shape){}

        void setShape(ShapeType s) {shapeType = s;}

        void setId(int _id) {shape_ID = _id;}

        void setPen(Qt::GlobalColor color);

        void setPen(Qt::GlobalColor, int width, Qt::PenStyle, Qt::PenCapStyle, Qt::PenJoinStyle);

        void setBrush(Qt::GlobalColor, Qt::BrushStyle);

        void defaultStyle();

        virtual ~Shape() {}
        /**
         * @brief Draws and renders the shape in the rendering area.
         * @param x
         * @param y
         */

        virtual void draw(const int x, const int y) = 0;
        /**
         * @brief Moves the shape to the specified coordinates.
         * @param x
         * @param y
         */

        virtual void move(const int x, const int y) = 0;
        /**
         * @brief Calculates the perimeter.
         * @return the perimeter
         */

        virtual double perimeter() = 0;
        /**
         * @brief Calculates the area.
         * @return the area
         */

        virtual double area() = 0;
        /**
         * @brief deletes the shape from the render screen
         */

        virtual void remove() = 0;

    private:
        int shape_ID;
        ShapeType shapeType;

};

class Line : public Shape
{
    public:
        Line(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::Line) {}

        ~Line() override {}

        void setPoints(const QPoint& begin, const QPoint& end);

        void draw(const int x, const int y)  override;

        void move(const int x, const int y) override;

        void remove() override;

        double perimeter() override {return 0;}

        double area() override {return 0;}

        QPoint& getBeginPoint() { return begin;}

        QPoint& getEndPoint() {return end;}

    private:
        QPoint begin;
        QPoint end;

};

class Polyline : public Shape
{
    public:
        Polyline(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::Polyline) {}

        ~Polyline()  override {}

        void addPoint(const QPointF& point);

        void draw(const int x, const int y)  override;

        void move(const int x, const int y) override;

        void remove() override;

        double perimeter() override {return 0;}

        double area() override {return 0;}

        vector<QPointF>& getPoints() {return points;}

    private:
        vector<QPointF> points;

};

class Polygon : public Shape
{
    public:
        Polygon(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::Polygon) {}

        ~Polygon() override {}

        void addPoint(const QPointF& point);

        void draw(const int x, const int y)  override;

        void move(const int x, const int y) override;

        void remove() override;

        double perimeter() override;

        double area() override;

        vector<QPointF>& getPoints() { return points;}

    private:
        vector<QPointF> points;

};

class Rectangle : public Shape
{
    public:
        Rectangle(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::Rectangle) {}

        ~Rectangle() override {}

        void setPosition(const QPoint& point) {position = point;}

        void setDimensions(int width, int height);

        void draw(const int x, const int y)  override;

        double perimeter() override;

        double area() override;

        void move(const int x, const int y) override;

        void remove() override;

        QPoint& getPosition() {return position;}

        int getWidth() {return width;}

        int getHeight() {return height;}

    private:
        QPoint position;
        int width, height;

};

class Ellipse : public Shape
{
    public:
        Ellipse(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::Ellipse) {}

        ~Ellipse() override {}

        void setPosition(const QPointF& point) {position = point;}

        void setDimensions(float width, float height) {this->width = width; this->height = height;}

        void draw(const int x, const int y)  override;

        double perimeter() override;

        double area() override;

        void move(const int x, const int y) override;

        void remove() override;

        QPointF& getPosition() {return position;}

        double getWidth() {return width;}

        double getHeight() {return height;}

    private:
        QPointF position;
        double width, height;

};

class Circle : public Shape
{
    public:
        Circle(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::Circle) {}

        ~Circle() override {}

        void setPosition(const QPointF& point) {position = point;}

        void setRadius(double radius) {this->radius = radius;}

        void setDimensions(double radius);

        void draw(const int x, const int y)  override;

        double perimeter() override;

        double area() override;

        void move(const int x, const int y) override;

        void remove() override;

        QPointF& getPosition() {return position;}

        double getRadius() {return radius;}

    private:
        QPointF position;
        double radius;

};

#endif // SHAPE_H
