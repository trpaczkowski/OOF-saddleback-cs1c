#include <QApplication>
#include <QPainter>
#include "vector.h"

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
