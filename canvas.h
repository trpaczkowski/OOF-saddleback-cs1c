#ifndef CANVAS_H
#define CANVAS_H


#include "readfile.h"

#include <QMessageBox>

class Canvas:public QWidget
{

    public:
        Canvas(QWidget *parent = 0);

        QSize sizeHint() const override;
        QSize minimumSizeHint() const override;

        int getRealID()
        {
            return IDCount;
        }

        void shapeAdd(Shape* shapeIn)
        {
            shapeList.push_back(shapeIn);
            IDCount++;

        }

        int getSizing()
        {
            return shapeList.size();
        }

        void shapeRemove(int indexRemove)
        {
            int vecCount = 0;
            bool found = false;
            //Delete operator
            vector<Shape*>::iterator delIt = shapeList.begin();
            while (found == false && vecCount < shapeList.size())
            {
                if ((*delIt)->getId() == indexRemove /*indexRemove == vecCount*/)
                {
                    shapeList.erase(delIt);
                    found = true;
                }
            vecCount++;
            delIt++;
            }
        }//END ShapeRemove

        void shapeMove(int indexMove, int coordMove, int x, int y)
        {
            int vecCount = 0;
            bool found = false;
            //Delete operator
            vector<Shape*>::iterator delIt = shapeList.begin();
            while (found == false && vecCount < shapeList.size())
            {
                if ((*delIt)->getId() == indexMove /*indexRemove == vecCount*/)
                {
                    (*delIt)->move(x, y, coordMove);
                    found = true;
                }
            vecCount++;
            delIt++;
            }

        }

        public:
        void paintEvent(QPaintEvent *event) override;

   private:
        vector<Shape*> shapeList; //Keeps track of shapes
        int IDCount{0};
        //ReadFile fileRead;


};


#endif // CANVAS_H
