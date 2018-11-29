#ifndef CANVAS_H
#define CANVAS_H

#include<QPainter>
#include<QWidget>
#include<QPen>
#include<QBrush>

#include "shape.h"
#include "vector.h"

class Canvas:public QWidget
{

    public:
        Canvas(QWidget *parent = 0);

        QSize sizeHint() const override;
        QSize minimumSizeHint() const override;

        int listSize(){
            return shapeList.size();
        }

        int rando() {return 5;}
        vector<Shape*> shapeList; //Keeps track of shapes


    protected:
        void paintEvent(QPaintEvent *event) override;


};


#endif // CANVAS_H
