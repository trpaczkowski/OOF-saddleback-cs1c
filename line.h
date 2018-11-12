#include <QApplication>
#include <QPainter>
#include "vector.h"

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
