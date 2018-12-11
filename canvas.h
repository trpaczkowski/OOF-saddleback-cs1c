/*
 *  2D Graphics Modeler
 *  December 2018
 *
 *  Oscar Lopez <olopez23@saddleback.edu>
 *  Jeff Adams <jadams62@saddleback.edu>
 *  Isaac Estrada <iestrada5@saddleback.edu>
 *  Caroline Ta <tta24@saddleback.edu>
 *  Travis Nguyen <tnguyen603@saddleback.edu>
 *  Taylor Paczkowski <tpaczkowski0@saddleback.edu>
 *  
 *  Descr: 2D Graphics Modeler for CS1C Fall 2018
 *  Teacher: John Kath
 *
 *  Draws shapes using QPainter. Shapes can be loaded from a file, added
 *  to a vector, manipulated and later saved. A login is required to access
 *  the program.
 *
 **/
/*
    File: canvas.h
    Base class of all renderable objects
*/

#ifndef CANVAS_H
#define CANVAS_H

#include <QFile>
#include <QTextStream>

#include "shape.h"

#include <QWidget>

#include <QMessageBox>

#include <QCoreApplication>

#include <QDir>

class Canvas:public QWidget
{

    public:
        Canvas(QWidget *parent = 0);

        QSize sizeHint() const override;
        QSize minimumSizeHint() const override;

        int getRealID(){return IDCount;}

        vector<Shape*> GetList(){return shapeList;}

        void shapeAdd(Shape* shapeIn);

        int getSizing(){return shapeList.size();}

        void shapeRemove(int indexRemove);//Shape remove

        void shapeMove(int indexMove, int coordMove, int x, int y); //Move shape

        void paintEvent(QPaintEvent *event) override; //Paint event ovverride

        void writeShapeFile(); //Writing to shape File

   private:
        vector<Shape*> shapeList; //Keeps track of shapes
        int IDCount{0};//Count of total amount of shapes added to canvas

        void readShapeFile(); //Read Shape File

        //STRING TO QT
        ShapeType stringToShapeType(QString shapeTypeStr);

        Qt::GlobalColor strToQTColor(QString strColorIn);

        Qt::PenCapStyle strToQTCapStyle(QString penCapStyleStrIn);

        Qt::PenStyle strToQTPenStyle(QString penStyleStrIn);

        Qt::PenJoinStyle strToQTPenJoinStyle(QString penJoinStyleStrIn);

        Qt::BrushStyle strToQTBushStyle(QString brushStyleStr);

        Qt::AlignmentFlag strToQTAlignment(QString alignStrIn);

        QFont::Style strToQTTextStyle(QString textFontStyleStrIn);

        QFont::Weight strToQTTextWeight(QString textFontWeightStrIn);

        //QT TO STRING
       /////////////////////////////////////////////////////////////////////////////////////////////////////////

        QString QTColorToStr(QColor strColorIn);

        QString QTCapStyleToStr(Qt::PenCapStyle penCapStyleStrIn);

        QString   QTPenStyleToStr(Qt::PenStyle penStyleStrIn);

        QString QTPenJoinStyleToStr(Qt::PenJoinStyle penJoinStyleStrIn);

        QString QTBushStyleToStr(Qt::BrushStyle brushStyleStr);

        QString QTAlignmentToStr(Qt::AlignmentFlag  alignStrIn);

         QString QTTextStyleToStr(QFont::Style textFontStyleStrIn);

        QString QTTextWeightToStr(int textFontWeightStrIn);

};


#endif // CANVAS_H
