#ifndef SHAPE_H
#define SHAPE_H

#include <QPaintDevice>
#include <QPoint>
#include <QString>
#include <QPainter>
#include "vector.h"

using namespace VecSTD;

//HELLo
 enum class ShapeType {NoShape, LineType, PolylineType, PolygonType, RectangleType, EllipseType, TextType};
class Shape : public QPainter
{
    public:
        QPainter painter;

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

        virtual void move(const int x, const int y, int coordNum) = 0;
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

        //virtual void remove() = 0;

    private:
        int shape_ID;
        ShapeType shapeType;

};

class Line : public Shape
{
    public:
        Line(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::LineType) {}

        ~Line() override {}

        void setPoints(const QPoint& begin, const QPoint& end);

        void draw(const int x, const int y) override;

        void draw() override
        {

        }

        virtual void draw(QPaintDevice *device) override
        {
//            QPen myPen;
//            myPen.setColor(Qt::GlobalColor::blue);
//            painter.setPen(myPen);
//            if(painter.pen().color() == Qt::GlobalColor::blue)
//            qDebug ("message %d, says: %s",5,"hello2");

            painter.begin(device);
            painter.drawLine(begin,end);
            painter.drawText(begin,QString::number(getId()));
            painter.end();
        }

        void move(const int x, const int y, int coordNum) override;

        //void remove() override;

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
        Polyline(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::PolylineType) {}

        ~Polyline()  override {}

        void addPoint(const QPointF& point);

        void addNumPoints(int numIn){ numPoints = numIn;}

        void draw(const int x, const int y)  override;

        virtual void draw() override
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
            painter.drawText(points[0],QString::number(getId()));
            painter.end();
        }

        void move(const int x, const int y, int coordNum) override;

        //void remove() override;

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
        Polygon(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::PolygonType) {}

        ~Polygon() override {}

        void addPoint(const QPointF& point);

        void addNumPoints(int numIn){ numPoints = numIn;}

        void draw(const int x, const int y)  override;

        virtual void draw() override
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
            painter.drawText(points[0],QString::number(getId()));
            painter.end();
        }

        void move(const int x, const int y, int coordNum) override;

        //void remove() override;

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
        Rectangle(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::RectangleType) {}

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
            painter.drawText(position,QString::number(getId()));
            painter.end();
        }

        double perimeter() override;

        double area() override;

        void move(const int x, const int y, int coordNum) override;

        //void remove() override;

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
        Ellipse(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::EllipseType) {}

        ~Ellipse() override {}

        void setPosition(const QPointF& point) {position = point;}

        void setDimensions(float width, float height) {this->width = width; this->height = height;}

        void draw(const int x, const int y)  override;

        virtual void draw() override
        {

        }

        void draw(QPaintDevice *device) override
        {
            painter.begin(device);
            painter.drawEllipse(position.x(), position.y(),width,height);
            painter.drawText(position,QString::number(getId()));
            painter.end();
        }

        double perimeter() override;

        double area() override;

        void move(const int x, const int y, int coordNum) override;

        //void remove() override;

        QPointF& getPosition() {return position;}

        double getWidth() {return width;}

        double getHeight() {return height;}

    private:
        QPointF position;
        double width, height;

};

class Text: public Shape
{
    public:
        Text(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::TextType) {}

        ~Text() override {}

        void setPosition(const QPoint& point) {position = point;}

        void setDimensions(int w, int h);

        void draw(const int x, const int y) override;

        virtual void draw() override
        {

        }

        void draw(QPaintDevice* device) override
        {
            painter.begin(device);
            painter.drawText(position.x(), position.y(), width, height, alignmentFlags, text);
            painter.drawText(position,QString::number(getId()));
            painter.end();
        }

        void move(const int x, const int y, int coordNum) override;

        //void remove() override{}

        double area() override;

        double perimeter() override;

        void setAlignment(Qt::AlignmentFlag flags);

        void setFont(bool boldIn, bool italicIn, int pointSizeIn, int weightIn);

        void setText(const QString& textIn);

        void setPosition(int x, int y);

        QFont& getFont();

        Qt::AlignmentFlag getAlignment() const;

        QString getText() const;

        vector<QString> dimensionLabels();

        vector<int> getDimensions();

    private:
        QPoint            position;
        int               width;
        int               height;
        QFont             font;
        QString           text;
        Qt::AlignmentFlag alignmentFlags;


};

#endif // SHAPE_H
