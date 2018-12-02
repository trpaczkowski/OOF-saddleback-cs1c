#ifndef SHAPE_H
#define SHAPE_H

//#include <QApplication>
#include <QPainter>
#include "vector.h"

using namespace VecSTD;

//HELLo

class Shape : public QPainter
{
    public:
        QPainter painter;
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

        virtual void draw() =0;

        virtual void draw(QPaintDevice *device)= 0;

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

        void draw(const int x, const int y) override;

        void draw() override
        {

        }

        virtual void draw(QPaintDevice *device) override
        {
            painter.begin(device);
            painter.drawLine(begin,end);
            painter.end();
        }

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

        void addNumPoints(int numIn){ numPoints = numIn;}

        void draw(const int x, const int y)  override;

        virtual void draw()
        {

        }

        virtual void draw(QPaintDevice *device) override
        {
            painter.begin(device);
            for(int i = 0; i < numPoints; i++)
            {
                polyLinePointsAr[i] = points[i];
            }
            painter.drawPolyline(polyLinePointsAr, numPoints);
            painter.end();
        }

        void move(const int x, const int y) override;

        void remove() override;

        double perimeter() override {return 0;}

        double area() override {return 0;}

        vector<QPointF>& getPoints() {return points;}

    private:
        vector<QPointF> points;
        int numPoints;
        QPointF polyLinePointsAr[6];

};

class Polygon : public Shape
{
    public:
        Polygon(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::Polygon) {}

        ~Polygon() override {}

        void addPoint(const QPointF& point);

        void addNumPoints(int numIn){ numPoints = numIn;}

        void draw(const int x, const int y)  override;

        virtual void draw()
        {

        }

        virtual void draw(QPaintDevice *device) override
        {
            painter.begin(device);
            for(int i = 0; i < numPoints; i++)
            {
                polygonPointsAr[i] = points[i];
            }
            painter.drawPolygon(polygonPointsAr, numPoints);
            painter.end();
        }

        void move(const int x, const int y) override;

        void remove() override;

        double perimeter() override;

        double area() override;

        vector<QPointF>& getPoints() { return points;}

    private:
        vector<QPointF> points;
        int numPoints;
        QPointF polygonPointsAr[8];

};

class Rectangle : public Shape
{
    public:
        Rectangle(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::Rectangle) {}

        ~Rectangle() override {}

        void setPosition(const QPoint& point) {position = point;}

        void setDimensions(int width, int height);

        void draw(const int x, const int y)  override;

        virtual void draw() override
        {

        }

        void draw(QPaintDevice* device) override
        {
            painter.begin(device);
            painter.drawRect(position.x(),position.y(), width,height);
            painter.end();
        }

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

        virtual void draw()
        {

        }

        void draw(QPaintDevice *device)
        {
            painter.begin(device);
            painter.drawEllipse(position.x(), position.y(),width,height);
            painter.end();
        }

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



#endif // SHAPE_H
