#ifndef SHAPE_H
#define SHAPE_H

#include <QPaintDevice>
#include <QPoint>
#include <QString>
#include <QPainter>
#include "vector.h"

using namespace VecSTD;

//HELLo
const QString shapeTypeStr[7] ={"No Shape", "Line", "Polyline", "Polygon", "Rectangle", "Ellipse", "Text"} ;
 enum class ShapeType {NoShape, LineType, PolylineType, PolygonType, RectangleType, EllipseType, TextType, SquareType, CircleType};
class Shape : public QPainter
{
    public:
        QPainter painter;

        QPen penType;

        QBrush brushType;

        ShapeType getShape() const {return shapeType;}

        int getId() const {return shape_ID;}

        QPen getPen() const {return penType;}

        Shape(QPaintDevice* device = nullptr, int id = -1, ShapeType shape = ShapeType::NoShape) :

             QPainter(device), shape_ID(id), shapeType(shape){}

        void setShape(ShapeType s) {shapeType = s;}

        void setId(int _id) {shape_ID = _id;}

        void setPen(Qt::GlobalColor color);

        void setPen(QPen pen){penType = pen;}

        void setPen(Qt::GlobalColor, int width, Qt::PenStyle, Qt::PenCapStyle, Qt::PenJoinStyle);

        void setBrush(Qt::GlobalColor, Qt::BrushStyle);

        void setBrush(QBrush brush){brushType = brush;}

        QBrush getBrush() {return brushType;}

        void defaultStyle();

        virtual ~Shape() {}

        virtual void draw() =0;

        virtual void draw(QPaintDevice *device)= 0;

        virtual void move(const int x, const int y, int coordNum) = 0;

        virtual double perimeter() = 0;

        virtual double area() = 0;

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

        void draw() override{}

        virtual void draw(QPaintDevice *device) override
        {
            painter.begin(device);
            painter.setPen(penType);
            painter.setBrush(brushType);
            painter.drawLine(begin,end);
            painter.drawText(begin,QString::number(getId()));
            painter.end();
        }

        void move(const int x, const int y, int coordNum) override;

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

        virtual void draw() override{}

        virtual void draw(QPaintDevice *device) override
        {
            painter.begin(device);
            for(int i = 0; i < numPoints; i++)
            {
                polyLinePointsAr[i] = points[i];
            }
            painter.setPen(penType);
            painter.setBrush(brushType);
            painter.drawPolyline(polyLinePointsAr, numPoints);
            painter.drawText(points[0],QString::number(getId()));
            painter.end();
        }

        void move(const int x, const int y, int coordNum) override;

        double perimeter() override {return 0;}

        double area() override {return 0;}

        vector<QPointF>& getPoints() {return points;}

        int getNumPoints() {return numPoints;}

    private:
        vector<QPointF> points;
        int numPoints;
        QPointF polyLinePointsAr[8];

};

class Polygon : public Shape
{
    public:
        Polygon(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id, ShapeType::PolygonType) {}

        ~Polygon() override {}

        void addPoint(const QPointF& point);

        void addNumPoints(int numIn){ numPoints = numIn;}

        virtual void draw() override{}

        virtual void draw(QPaintDevice *device) override
        {
            painter.begin(device);
            for(int i = 0; i < numPoints; i++)
            {
                polygonPointsAr[i] = points[i];
            }
            painter.setPen(penType);
            painter.setBrush(brushType);
            painter.drawPolygon(polygonPointsAr, numPoints);
            painter.drawText(points[0],QString::number(getId()));
            painter.end();
        }

        void move(const int x, const int y, int coordNum) override;

        double perimeter() override;

        double area() override;

        vector<QPointF>& getPoints() { return points;}

        int getNumPoints() {return numPoints;}

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

        virtual void draw() override{}

        void draw(QPaintDevice* device) override
        {
            painter.begin(device);
            painter.setPen(penType);
            painter.setBrush(brushType);
            painter.drawRect(position.x(),position.y(), width,height);
            painter.drawText(position,QString::number(getId()));
            painter.end();
        }

        double perimeter() override;

        double area() override;

        void move(const int x, const int y, int coordNum) override;

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

        virtual void draw() override{}

        void draw(QPaintDevice *device) override
        {
            painter.begin(device);
            painter.setPen(penType);
            painter.setBrush(brushType);
            painter.drawEllipse(position.x(), position.y(),width,height);
            painter.drawText(position,QString::number(getId()));
            painter.end();
        }

        double perimeter() override;

        double area() override;

        void move(const int x, const int y, int coordNum) override;

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

        virtual void draw() override{}

        void draw(QPaintDevice* device) override
        {
            painter.begin(device);
            painter.setFont(font);
            painter.setPen(penType);
            painter.drawText(position.x(), position.y(), width, height, alignmentFlags, text);
            painter.drawText(position,QString::number(getId()));
            painter.end();
        }

        void move(const int x, const int y, int coordNum) override;

        double area() override;

        double perimeter() override;

        void setAlignment(Qt::AlignmentFlag flags);

        void setFont(QString fontFamIn, QFont::Style fontStyleIn, int pointSizeIn, QFont::Weight weightIn, Qt::GlobalColor colorIn);

        void setFont(QFont fontIN){font = fontIN;}

        void setText(const QString& textIn);

        void setPosition(int x, int y);

        QFont& getFont();

        Qt::AlignmentFlag getAlignment() const;

        QString getText() const;

        vector<QString> dimensionLabels();

        vector<int> getDimensions();

        QPoint getPosition() {return position;}
        int getWidth() {return width;}
        int getHeight() {return height;}

    private:
        QPoint            position;
        int               width;
        int               height;
        QFont             font;
        QString           text;
        Qt::AlignmentFlag alignmentFlags;


};

#endif // SHAPE_H
