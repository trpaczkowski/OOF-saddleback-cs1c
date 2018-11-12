#include <QApplication>
#include <QPainter>
#include "vector.h"

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
