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

        void shapeRemove(int indexRemove)
        {
            //indexRemove--;// Will get to correct index

            qDebug ("In process of removing");
            int vecCount = 0;
            bool found = false;
            //Delete operator
            vector<Shape*>::iterator delIt = shapeList.begin();
            qDebug ("In process of removing 41");
            while (found == false && vecCount < shapeList.size())
            {qDebug ("In process of removing 43");
                if (/*(*delIt)->getId() == indexRemove*/indexRemove == vecCount)
                {qDebug ("In process of removing 45");
                    shapeList.erase(delIt);
                    qDebug ("In process of removing 46");
                    found = true;
                    qDebug ("Shape deleted %d, says: %s",indexRemove,"DELETED");

                }
           qDebug ("In process of removing 51A"); ++delIt; qDebug ("In process of removing 51B");
            vecCount++;
            }
        }//END ShapeRemove

        void shapeMove(int indexMove, int x, int y)
        {
            shapeList[indexMove]->move(x, y, indexMove);
        }

        public:
        void paintEvent(QPaintEvent *event) override;

   private:
        vector<Shape*> shapeList; //Keeps track of shapes


};


#endif // CANVAS_H
