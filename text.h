#ifndef TEXT_H
#define TEXT_H

#include <QPainter>
#include <QString>
#include "Shape.h"

class Text : public Shape
{
    private:
        int text_id;
        int width, height;
        QPointF position;
        QString text;
        Qt::Alignment alignment;

    public:
        Text(QPaintDevice* device = nullptr, int id = -1) : Shape(device, id), text_id(id) {}
        
        void defaultStyle();
        
        QString getTextString() {return text;}
        int getId() {return text_id;}
        
        QPointF& getPosition() {return position;}
        void setPosition(QPointF& point) {position = point;}
        
        int getWidth() {return width;}
        int getHeight() {return height;}
        
        void setDimensions(int width, int height);
        void setTextString(QString textstring);
        void setAlignment(QString alignment);
        
        Qt::Alignment getAlignment () {return alignment;}
        
        ~Text() {}
        
        void draw(const int x, const int y);
        void move(const int x, const int y);
        
        double perimeter();
        double area();
        
        void remove();
};

#endif // TEXT_H
