#ifndef CANVAS_H
#define CANVAS_H

<<<<<<< HEAD
#include<QPainter>
#include<QWidget>
#include<QPen>
#include<QBrush>

#include "shape.h"
#include "vector.h"
=======

//#include<QPen>
//#include<QBrush>

#include "shape.h"

#include <QMessageBox>
>>>>>>> f10f7fc401ffd2c2bc22c0dc688ad62b4db56600

class Canvas:public QWidget
{

    public:
        Canvas(QWidget *parent = 0);

        QSize sizeHint() const override;
        QSize minimumSizeHint() const override;

<<<<<<< HEAD
        int listSize(){
            return shapeList.size();
        }

        int rando() {return 5;}
        vector<Shape*> shapeList; //Keeps track of shapes


    protected:
        void paintEvent(QPaintEvent *event) override;

=======
        void shapeAdd(Line* shapeIn)
        {
            shapeList.push_back(shapeIn);

        }

        int getSizing()
        {
            return shapeList.size();
        }

        int getpoint(int index)
        {
            QPoint first;
            first = shapeList[index]->getBeginPoint();
            return first.x();
           //shapeList[index]->draw();
        }



        public:
        void paintEvent(QPaintEvent *event) override;

   private:
        vector<Line*> shapeList; //Keeps track of shapes

>>>>>>> f10f7fc401ffd2c2bc22c0dc688ad62b4db56600

};


#endif // CANVAS_H
