#ifndef CANVAS_H
#define CANVAS_H


//#include<QPen>
//#include<QBrush>

#include "shape.h"

#include <QMessageBox>

class Canvas:public QWidget
{

    public:
        Canvas(QWidget *parent = 0);

        QSize sizeHint() const override;
        QSize minimumSizeHint() const override;

        void shapeAdd(Shape* shapeIn)
        {
            shapeList.push_back(shapeIn);

        }

        int getSizing()
        {
            return shapeList.size();
        }

        vector<Shape *> copyVector ()
        {
            vector <Shape *> temp;

            temp = shapeList;

            return temp;
        }

//        int getpoint(int index)
//        {
//            QPoint first;
//            first = shapeList[index]->getBeginPoint();
//            return first.x();
//           //shapeList[index]->draw();
//        }



        public:
        void paintEvent(QPaintEvent *event) override;

   private:
        vector<Shape*> shapeList; //Keeps track of shapes


};


#endif // CANVAS_H
