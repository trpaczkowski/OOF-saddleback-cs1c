#include <QApplication>
#include <QPainter>
#include "vector.h"

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
