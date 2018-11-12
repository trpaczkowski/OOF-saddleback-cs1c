#include <QApplication>
#include <QPainter>
#include "vector.h"

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
