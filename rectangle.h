#include <QApplication>
#include <QPainter>
#include "vector.h"

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
