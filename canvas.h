#ifndef CANVAS_H
#define CANVAS_H

#include <QFile>
#include <QTextStream>

#include "shape.h"

#include <QWidget>

#include <fstream>

#include <string>

#include <sstream> //string subtract

#include <stdlib.h> //atoi

//using namespace std;

#include <QMessageBox>

class Canvas:public QWidget
{

    public:
        Canvas(QWidget *parent = 0);

        QSize sizeHint() const override;
        QSize minimumSizeHint() const override;

        vector <Shape *> GetList()
        {
            return shapeList;
        }
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

        void writeShapeFile()
        {
            QFile myFile(":/shapeIO/img/shape.txt");

            if(!myFile.open( QIODevice::WriteOnly | QIODevice::Text))
            {
                qDebug("could not open file\n");
            }

            QTextStream fout(&myFile);
            vector<Shape*>::iterator i = shapeList.begin();
            while(i < shapeList.end()) //Write List
            {
               fout << endl; //Add space between shapes
               fout << "ShapeId: " << (*i)->getId() << endl;
               fout << "ShapeType: " << shapeTypeStr[int((*i)->getShape())] << endl;
                switch ((*i)->getShape())
                {
                case ShapeType::LineType:
                {
                    fout << "ShapeDimensions: " << dynamic_cast<Line*>(*i)->getBeginPoint().x();
                    break;
                }
                case ShapeType::PolylineType:
                {
                    break;
                }
                case ShapeType::PolygonType:
                {
                    break;
                }
                case ShapeType::RectangleType:
                {
                    break;
                }
                case ShapeType::EllipseType:
                {
                    break;
                }
                case ShapeType::TextType:
                {
                    break;
                }
                default: qDebug("Error write");
                }
                ++i;
            }

            myFile.flush();
            myFile.close();
        }

   private:
        vector<Shape*> shapeList; //Keeps track of shapes
        int IDCount{0};



        void readShapeFile()
        {
            vector<Shape*> shapeVec;

            QFile myFile(":/shapeIO/img/shape.txt");

            if(!myFile.open( QIODevice::ReadOnly | QIODevice::Text))
            {
                qDebug("could not open file\n");
            }

            QTextStream fileIn(&myFile);
            QString ignoreNewline;
            ignoreNewline = fileIn.readLine();//Removes empty line

            while(!fileIn.atEnd())
            {
                QString identifierTrash; //Will read in identifier and take out ex: "ShapeType:"
                QPen shapePen;
                QBrush shapeBrush;


                int shapeIDNum;
                QString shapeTypeStr;
                ShapeType shapeTypeEnum;

                //Read ShapeID
                fileIn >> identifierTrash;
                fileIn >> shapeIDNum;

                //Read shape type
                fileIn >> identifierTrash;
                fileIn >> shapeTypeStr;

                //Find correct enum
                shapeTypeEnum = stringToShapeType(shapeTypeStr);

                //Seperate to different shape types
                switch(shapeTypeEnum)
                {
                    //Line
                case ShapeType::LineType:
                {qDebug("line adding 134 canvas.h");
                    Line *addLine = new Line(this, 0);
                    QPen linePen;

                    //Store shape dimensions
                    QString coordStr;
                    QStringList coordVec;

                    fileIn >> identifierTrash;

                    coordStr = fileIn.readLine();
                    coordVec = coordStr.split(',');
                    QPoint coord1(coordVec[0].toInt(), coordVec[1].toInt());
                    QPoint coord2(coordVec[2].toInt(), coordVec[3].toInt());
                    addLine->setPoints(coord1, coord2);

                    //Store Pen color
                    fileIn >> identifierTrash;
                    QString penColorStr;
                    fileIn >> penColorStr;
                    linePen.setColor(strToQTColor(penColorStr));

                    //Store Pen Width;
                    fileIn >> identifierTrash;
                    int penWidth;
                    fileIn >> penWidth;
                    linePen.setWidth(penWidth);

                    //Store Pen Style
                    fileIn >> identifierTrash;
                    QString penStyleStr;
                    fileIn >> penStyleStr;
                    linePen.setStyle(strToQTPenStyle(penStyleStr));

                    //Store Pen Cap Style
                    fileIn >> identifierTrash;
                    QString penCapStyleStr;
                    fileIn >> penCapStyleStr;
                    linePen.setCapStyle(strToQTCapStyle(penCapStyleStr));

                    //Store Pen Join Style
                    fileIn >> identifierTrash;
                    QString penJoinStyleStr;
                    fileIn >> penJoinStyleStr;
                    linePen.setJoinStyle(strToQTPenJoinStyle(penJoinStyleStr));

                    addLine->setPen(linePen);
                    addLine->setId(shapeIDNum); //Set shape ID
                    addLine->setShape(ShapeType::LineType);
                    shapeAdd(addLine); //Adding shape

                    if(addLine->pen().color() == Qt::GlobalColor::blue){qDebug("corrrrrect");}

                    break;
                }
                  //PolyLine
                case ShapeType::PolylineType:
                {qDebug("polyline adding 189 canvas.h");
                    Polyline *addPolyLine = new Polyline(this, 0);
                    QPen polylinePen;

                    //Store shape dimensions
                    QString coordStr;
                    QStringList coordVec;

                    fileIn >> identifierTrash;

                    coordStr = fileIn.readLine();
                    coordVec = coordStr.split(',');
                    QPoint coord1(coordVec[0].toInt(), coordVec[1].toInt());
                    QPoint coord2(coordVec[2].toInt(), coordVec[3].toInt());

                    addPolyLine->addPoint(coord1); //Set points
                    addPolyLine->addPoint(coord2); //Set points

                    if(coordVec.size() > 4)//Check to see if more points
                    {
                        QPoint coord3(coordVec[4].toInt(), coordVec[5].toInt());
                        addPolyLine->addPoint(coord3); //Set points

                        if(coordVec.size() > 6)//If more points
                        {
                            QPoint coord4(coordVec[6].toInt(), coordVec[7].toInt());
                            addPolyLine->addPoint(coord4); //Set points

                            if(coordVec.size() > 8)//If more points
                            {
                                QPoint coord5(coordVec[8].toInt(), coordVec[9].toInt());
                                addPolyLine->addPoint(coord5); //Set points

                                if(coordVec.size() > 10)//If more points
                                {
                                    QPoint coord6(coordVec[10].toInt(), coordVec[11].toInt());
                                    addPolyLine->addPoint(coord6); //Set points


                                }
                            }
                        }
                    }


                    //Store Pen color
                    fileIn >> identifierTrash;
                    QString penColorStr;
                    fileIn >> penColorStr;
                    polylinePen.setColor(strToQTColor(penColorStr));

                    //Store Pen Width;
                    fileIn >> identifierTrash;
                    int penWidth;
                    fileIn >> penWidth;
                    polylinePen.setWidth(penWidth);

                    //Store Pen Style
                    fileIn >> identifierTrash;
                    QString penStyleStr;
                    fileIn >> penStyleStr;
                    polylinePen.setStyle(strToQTPenStyle(penStyleStr));

                    //Store Pen Cap Style
                    fileIn >> identifierTrash;
                    QString penCapStyleStr;
                    fileIn >> penCapStyleStr;
                    polylinePen.setCapStyle(strToQTCapStyle(penCapStyleStr));

                    //Store Pen Join Style
                    fileIn >> identifierTrash;
                    QString penJoinStyleStr;
                    fileIn >> penJoinStyleStr;
                    polylinePen.setJoinStyle(strToQTPenJoinStyle(penJoinStyleStr));

                    addPolyLine->setPen(polylinePen);
                    addPolyLine->setId(shapeIDNum);
                    addPolyLine->setShape(ShapeType::PolylineType);
                    addPolyLine->addNumPoints(coordVec.size()/2);
                    shapeAdd(addPolyLine); //Adding shape

                    break;
                }

                      //Polygon
                case ShapeType::PolygonType:
                {qDebug("polygon adding 257 canvas.h");
                    Polygon *addPolygon = new Polygon(this, 0);
                    QPen polygonPen;
                    QBrush polygonBrush;

                    //Store shape dimensions
                    QString coordStr;
                    QStringList coordVec;

                    fileIn >> identifierTrash;

                    coordStr = fileIn.readLine();
                    coordVec = coordStr.split(',');
                    QPoint coord1(coordVec[0].toInt(), coordVec[1].toInt());
                    QPoint coord2(coordVec[2].toInt(), coordVec[3].toInt());

                    addPolygon->addPoint(coord1); //Set points
                    addPolygon->addPoint(coord2); //Set points

                    if(coordVec.size() > 4)//Check to see if more points
                    {
                        QPoint coord3(coordVec[4].toInt(), coordVec[5].toInt());
                        addPolygon->addPoint(coord3); //Set points

                        if(coordVec.size() > 6)//If more points
                        {
                            QPoint coord4(coordVec[6].toInt(), coordVec[7].toInt());
                            addPolygon->addPoint(coord4); //Set points

                            if(coordVec.size() > 8)//If more points
                            {
                                QPoint coord5(coordVec[8].toInt(), coordVec[9].toInt());
                                addPolygon->addPoint(coord5); //Set points

                                if(coordVec.size() > 10)//If more points
                                {
                                    QPoint coord6(coordVec[10].toInt(), coordVec[11].toInt());
                                    addPolygon->addPoint(coord6); //Set points

                                    if(coordVec.size() > 12)//If more points
                                    {
                                        QPoint coord7(coordVec[12].toInt(), coordVec[13].toInt());
                                        addPolygon->addPoint(coord7); //Set points

                                        if(coordVec.size() > 14)//If more points
                                        {
                                            QPoint coord8(coordVec[14].toInt(), coordVec[15].toInt());
                                            addPolygon->addPoint(coord8); //Set points


                                        }
                                    }
                                }
                            }
                        }
                    }

                    //Store Pen color
                    fileIn >> identifierTrash;
                    QString penColorStr;
                    fileIn >> penColorStr;
                    polygonPen.setColor(strToQTColor(penColorStr));

                    //Store Pen Width;
                    fileIn >> identifierTrash;
                    int penWidth;
                    fileIn >> penWidth;
                    polygonPen.setWidth(penWidth);

                    //Store Pen Style
                    fileIn >> identifierTrash;
                    QString penStyleStr;
                    fileIn >> penStyleStr;
                    polygonPen.setStyle(strToQTPenStyle(penStyleStr));

                    //Store Pen Cap Style
                    fileIn >> identifierTrash;
                    QString penCapStyleStr;
                    fileIn >> penCapStyleStr;
                    polygonPen.setCapStyle(strToQTCapStyle(penCapStyleStr));

                    //Store Pen Join Style
                    fileIn >> identifierTrash;
                    QString penJoinStyleStr;
                    fileIn >> penJoinStyleStr;
                    polygonPen.setJoinStyle(strToQTPenJoinStyle(penJoinStyleStr));

                    //Store Brush Color
                    fileIn >> identifierTrash;
                    QString brushColorStr;
                    fileIn >> brushColorStr;
                    polygonBrush.setColor(strToQTColor(brushColorStr));

                    //Store BrushStyle
                    fileIn >> identifierTrash;
                    QString brushStyleStr;
                    fileIn >> brushStyleStr;
                    polygonBrush.setStyle(strToQTBushStyle(brushStyleStr));

                    addPolygon->setPen(polygonPen);
                    addPolygon->setBrush(polygonBrush);
                    addPolygon->setId(shapeIDNum);
                    addPolygon->setShape(ShapeType::PolygonType);
                    addPolygon->addNumPoints(coordVec.size()/2);
                    shapeAdd(addPolygon); //Adding shape
                    break;
                }
                   //Rectangle
                case ShapeType::RectangleType:
                {qDebug("rect adding 325 canvas.h");
                    Rectangle *addRect = new Rectangle(this, 0);
                    QPen rectPen;
                    QBrush rectBrush;

                    //Store shape dimensions
                    QString coordStr;
                    QStringList coordVec;

                    fileIn >> identifierTrash;

                    coordStr = fileIn.readLine();
                    coordVec = coordStr.split(',');
                    QPoint center(coordVec[0].toInt(), coordVec[1].toInt());
                    addRect->setPosition(center);
                    addRect->setDimensions(coordVec[3].toInt(), coordVec[2].toInt());

                    //Store Pen color
                    fileIn >> identifierTrash;
                    QString penColorStr;
                    fileIn >> penColorStr;
                    rectPen.setColor(strToQTColor(penColorStr));

                    //Store Pen Width;
                    fileIn >> identifierTrash;
                    int penWidth;
                    fileIn >> penWidth;
                    rectPen.setWidth(penWidth);

                    //Store Pen Style
                    fileIn >> identifierTrash;
                    QString penStyleStr;
                    fileIn >> penStyleStr;
                    rectPen.setStyle(strToQTPenStyle(penStyleStr));

                    //Store Pen Cap Style
                    fileIn >> identifierTrash;
                    QString penCapStyleStr;
                    fileIn >> penCapStyleStr;
                    rectPen.setCapStyle(strToQTCapStyle(penCapStyleStr));

                    //Store Pen Join Style
                    fileIn >> identifierTrash;
                    QString penJoinStyleStr;
                    fileIn >> penJoinStyleStr;
                    rectPen.setJoinStyle(strToQTPenJoinStyle(penJoinStyleStr));

                    //Store Brush Color
                    fileIn >> identifierTrash;
                    QString brushColorStr;
                    fileIn >> brushColorStr;
                    rectBrush.setColor(strToQTColor(brushColorStr));

                    //Store BrushStyle
                    fileIn >> identifierTrash;
                    QString brushStyleStr;
                    fileIn >> brushStyleStr;
                    rectBrush.setStyle(strToQTBushStyle(brushStyleStr));

                    addRect->setPen(rectPen);
                    addRect->setBrush(rectBrush);
                    addRect->setId(shapeIDNum);
                    addRect->setShape(ShapeType::RectangleType);
                    shapeAdd(addRect); //Adding shape
                    break;
                }
                    //Square
                case ShapeType::SquareType:
                {qDebug("square adding 393 canvas.h");
                    Rectangle *addSquare = new Rectangle(this, 0);
                    QPen sqrPen;
                    QBrush sqrBrush;

                    //Store shape dimensions
                    QString coordStr;
                    QStringList coordVec;

                    fileIn >> identifierTrash;

                    coordStr = fileIn.readLine();
                    coordVec = coordStr.split(',');
                    QPoint center(coordVec[0].toInt(), coordVec[1].toInt());
                    addSquare->setPosition(center);
                    addSquare->setDimensions(coordVec[2].toInt(), coordVec[2].toInt()); //Same length and width

                    //Store Pen color
                    fileIn >> identifierTrash;
                    QString penColorStr;
                    fileIn >> penColorStr;
                    sqrPen.setColor(strToQTColor(penColorStr));

                    //Store Pen Width;
                    fileIn >> identifierTrash;
                    int penWidth;
                    fileIn >> penWidth;
                    sqrPen.setWidth(penWidth);

                    //Store Pen Style
                    fileIn >> identifierTrash;
                    QString penStyleStr;
                    fileIn >> penStyleStr;
                    sqrPen.setStyle(strToQTPenStyle(penStyleStr));

                    //Store Pen Cap Style
                    fileIn >> identifierTrash;
                    QString penCapStyleStr;
                    fileIn >> penCapStyleStr;
                    sqrPen.setCapStyle(strToQTCapStyle(penCapStyleStr));

                    //Store Pen Join Style
                    fileIn >> identifierTrash;
                    QString penJoinStyleStr;
                    fileIn >> penJoinStyleStr;
                    sqrPen.setJoinStyle(strToQTPenJoinStyle(penJoinStyleStr));

                    //Store Brush Color
                    fileIn >> identifierTrash;
                    QString brushColorStr;
                    fileIn >> brushColorStr;
                    sqrBrush.setColor(strToQTColor(brushColorStr));

                    //Store BrushStyle
                    fileIn >> identifierTrash;
                    QString brushStyleStr;
                    fileIn >> brushStyleStr;
                    sqrBrush.setStyle(strToQTBushStyle(brushStyleStr));

                    addSquare->setPen(sqrPen);
                    addSquare->setBrush(sqrBrush);
                    addSquare->setId(shapeIDNum);
                    addSquare->setShape(ShapeType::RectangleType);
                    shapeAdd(addSquare); //Adding shape
                    break;
                }
                    //Ellipse
                case ShapeType::EllipseType:
                {qDebug("elipse adding 461 canvas.h");
                    Ellipse *addEllipse = new Ellipse(this, 0);
                    QPen ellipsePen;
                    QBrush ellipseBrush;

                    //Store shape dimensions
                    QString coordStr;
                    QStringList coordVec;

                    fileIn >> identifierTrash;

                    coordStr = fileIn.readLine();
                    coordVec = coordStr.split(',');
                    QPoint center(coordVec[0].toInt(), coordVec[1].toInt());
                    addEllipse->setPosition(center);
                    addEllipse->setDimensions(coordVec[2].toInt(), coordVec[3].toInt()); //Same length and width

                    //Store Pen color
                    fileIn >> identifierTrash;
                    QString penColorStr;
                    fileIn >> penColorStr;
                    ellipsePen.setColor(strToQTColor(penColorStr));

                    //Store Pen Width;
                    fileIn >> identifierTrash;
                    int penWidth;
                    fileIn >> penWidth;
                    ellipsePen.setWidth(penWidth);

                    //Store Pen Style
                    fileIn >> identifierTrash;
                    QString penStyleStr;
                    fileIn >> penStyleStr;
                    ellipsePen.setStyle(strToQTPenStyle(penStyleStr));

                    //Store Pen Cap Style
                    fileIn >> identifierTrash;
                    QString penCapStyleStr;
                    fileIn >> penCapStyleStr;
                    ellipsePen.setCapStyle(strToQTCapStyle(penCapStyleStr));

                    //Store Pen Join Style
                    fileIn >> identifierTrash;
                    QString penJoinStyleStr;
                    fileIn >> penJoinStyleStr;
                    ellipsePen.setJoinStyle(strToQTPenJoinStyle(penJoinStyleStr));

                    //Store Brush Color
                    fileIn >> identifierTrash;
                    QString brushColorStr;
                    fileIn >> brushColorStr;
                    ellipseBrush.setColor(strToQTColor(brushColorStr));

                    //Store BrushStyle
                    fileIn >> identifierTrash;
                    QString brushStyleStr;
                    fileIn >> brushStyleStr;
                    ellipseBrush.setStyle(strToQTBushStyle(brushStyleStr));

                    addEllipse->setPen(ellipsePen);
                    addEllipse->setBrush(ellipseBrush);
                    addEllipse->setId(shapeIDNum);
                    addEllipse->setShape(ShapeType::EllipseType);
                    shapeAdd(addEllipse); //Adding shape
                    break;
                }
                    //Circle
                case ShapeType::CircleType:
                {qDebug("circ adding 529 canvas.h");
                    Ellipse *addCircle = new Ellipse(this, 0);
                    QPen circPen;
                    QBrush circBrush;

                    //Store shape dimensions
                    QString coordStr;
                    QStringList coordVec;

                    fileIn >> identifierTrash;

                    coordStr = fileIn.readLine();
                    coordVec = coordStr.split(',');
                    QPoint center(coordVec[0].toInt(), coordVec[1].toInt());
                    addCircle->setPosition(center);
                    addCircle->setDimensions(coordVec[2].toInt(), coordVec[2].toInt()); //Same length and width

                    //Store Pen color
                    fileIn >> identifierTrash;
                    QString penColorStr;
                    fileIn >> penColorStr;
                    circPen.setColor(strToQTColor(penColorStr));

                    //Store Pen Width;
                    fileIn >> identifierTrash;
                    int penWidth;
                    fileIn >> penWidth;
                    circPen.setWidth(penWidth);

                    //Store Pen Style
                    fileIn >> identifierTrash;
                    QString penStyleStr;
                    fileIn >> penStyleStr;
                    circPen.setStyle(strToQTPenStyle(penStyleStr));

                    //Store Pen Cap Style
                    fileIn >> identifierTrash;
                    QString penCapStyleStr;
                    fileIn >> penCapStyleStr;
                    circPen.setCapStyle(strToQTCapStyle(penCapStyleStr));

                    //Store Pen Join Style
                    fileIn >> identifierTrash;
                    QString penJoinStyleStr;
                    fileIn >> penJoinStyleStr;
                    circPen.setJoinStyle(strToQTPenJoinStyle(penJoinStyleStr));

                    //Store Brush Color
                    fileIn >> identifierTrash;
                    QString brushColorStr;
                    fileIn >> brushColorStr;
                    circBrush.setColor(strToQTColor(brushColorStr));

                    //Store BrushStyle
                    fileIn >> identifierTrash;
                    QString brushStyleStr;
                    fileIn >> brushStyleStr;
                    circBrush.setStyle(strToQTBushStyle(brushStyleStr));

                    addCircle->setPen(circPen);
                    addCircle->setBrush(circBrush);
                    addCircle->setId(shapeIDNum);
                    addCircle->setShape(ShapeType::EllipseType);
                    shapeAdd(addCircle); //Adding shape
                    break;
                }
                    //Text
                case ShapeType::TextType:
                {qDebug("text adding 597 canvas.h");
                    Text *addText = new Text(this, 0);
                    QPen textPen;
                    QFont textFont;

                    //Store shape dimensions
                    QString coordStr;
                    QStringList coordVec;

                    fileIn >> identifierTrash;

                    coordStr = fileIn.readLine();
                    coordVec = coordStr.split(',');
                    QPoint center(coordVec[0].toInt(), coordVec[1].toInt());
                    addText->setPosition(center);
                    addText->setDimensions(coordVec[2].toInt(), coordVec[3].toInt()); //Same length and width

                    //Store text
                    fileIn >> identifierTrash;
                    QString textStr;
                    textStr = fileIn.readLine();
                    addText->setText(textStr);

                    //Store Pen color
                    fileIn >> identifierTrash;
                    QString penColorStr;
                    fileIn >> penColorStr;
                    textPen.setColor(strToQTColor(penColorStr));

                    //Store Alignment
                    fileIn >> identifierTrash;
                    QString alignStr;
                    fileIn >> alignStr;
                    addText->setAlignment(strToQTAlignment(alignStr));

                    //Store point size
                    fileIn >> identifierTrash;
                    int pointSize;
                    fileIn >> pointSize;
                    textFont.setPointSize(pointSize);

                    //Store family
                    fileIn >> identifierTrash;
                    QString textFamilyStr;
                    textFamilyStr = fileIn.readLine();
                    textFont.setFamily(textFamilyStr);

                    //Store Font style
                    fileIn >> identifierTrash;
                    QString textFontStyleStr;
                    fileIn >> textFontStyleStr;
                    textFont.setStyle(strToQTTextStyle(textFontStyleStr));

                    //Store Font weight
                    fileIn >> identifierTrash;
                    QString textFontWeightStr;
                    fileIn >> textFontWeightStr;
                    textFont.setWeight(strToQTTextWeight(textFontWeightStr));

                    addText->setPen(textPen);
                    addText->setFont(textFont);
                    addText->setId(shapeIDNum);
                    addText->setShape(ShapeType::TextType);
                    shapeAdd(addText); //Adding shape

                    break;
                }
                default: {qDebug("error reading file");}
                }//End Switch
                ignoreNewline = fileIn.readLine();//Removes empty line
            }//EndWhile
            myFile.close();
            if(!myFile.isOpen())qDebug("End of adding shapes");

        }

        ShapeType stringToShapeType(QString shapeTypeStr)
        {
            ShapeType shapeTypeEnum;

            if(shapeTypeStr.compare("Line") == 0)//Equals 0 when equal
            {
                shapeTypeEnum = ShapeType::LineType;
            }
            else if(shapeTypeStr.compare("Polyline") == 0)//Equals 0 when equal
            {
                shapeTypeEnum = ShapeType::PolylineType;
            }
            else if(shapeTypeStr.compare("Polygon") == 0)//Equals 0 when equal
            {
                shapeTypeEnum = ShapeType::PolygonType;
            }
            else if(shapeTypeStr.compare("Rectangle") == 0)//Equals 0 when equal
            {
                shapeTypeEnum = ShapeType::RectangleType;
            }
            else if(shapeTypeStr.compare("Square") == 0)//Equals 0 when equal
            {
                shapeTypeEnum = ShapeType::SquareType;
            }
            else if(shapeTypeStr.compare("Ellipse") == 0)//Equals 0 when equal
            {
                shapeTypeEnum = ShapeType::EllipseType;
            }
            else if(shapeTypeStr.compare("Circle") == 0)//Equals 0 when equal
            {
                shapeTypeEnum = ShapeType::CircleType;
            }
            else if(shapeTypeStr.compare("Text") == 0)//Equals 0 when equal
            {
                shapeTypeEnum = ShapeType::TextType;
            }
            else
            {
                shapeTypeEnum = ShapeType::NoShape;
            }


            return shapeTypeEnum;
        }

        Qt::GlobalColor strToQTColor(QString strColorIn)
        {
            if(strColorIn == "blue")
                return Qt::blue;
            else if(strColorIn == "red")
                return Qt::red;
            else if(strColorIn == "green")
                return Qt::green;
            else if(strColorIn == "yellow")
                return Qt::yellow;
            else if(strColorIn == "black")
                return Qt::black;
            else if(strColorIn == "white")
                return Qt::white;
            else if(strColorIn == "cyan")
                return Qt::cyan;
            else if(strColorIn == "magenta")
                return Qt::magenta;
            else
                return Qt::gray;
        }

        Qt::PenCapStyle strToQTCapStyle(QString penCapStyleStrIn)
        {
            if(penCapStyleStrIn == "FlatCap")
                return Qt::FlatCap;
            else if(penCapStyleStrIn == "SquareCap")
                return Qt::SquareCap;
            else
                return Qt::RoundCap;
        }

        Qt::PenStyle strToQTPenStyle(QString penStyleStrIn)
        {
            if(penStyleStrIn == "NoPen")
                return Qt::NoPen;
            else if(penStyleStrIn == "SolidLine")
                return Qt::SolidLine;
            else if(penStyleStrIn == "DashLine")
                return Qt::DashLine;
            else if(penStyleStrIn == "DotLine")
                return Qt::DotLine;
            else if(penStyleStrIn == "DashDotLine")
                return Qt::DashDotLine;
            else
                return Qt::DashDotDotLine;
        }

        Qt::PenJoinStyle strToQTPenJoinStyle(QString penJoinStyleStrIn)
        {
            if(penJoinStyleStrIn == "MiterJoin")
                return Qt::MiterJoin;
            else if(penJoinStyleStrIn == "BevelJoin")
                return Qt::BevelJoin;
            else
                return Qt::RoundJoin;
        }

        Qt::BrushStyle strToQTBushStyle(QString brushStyleStr)
        {
            if(brushStyleStr == "SolidPattern")
                return Qt::SolidPattern;
            else if(brushStyleStr == "HorPattern")
                return Qt::HorPattern;
            else if(brushStyleStr == "VerPattern")
                return Qt::VerPattern;
            else
                return Qt::NoBrush;
        }

        Qt::AlignmentFlag strToQTAlignment(QString alignStrIn)
        {
            if(alignStrIn == "AlignLeft")
                return Qt::AlignLeft;
            else if(alignStrIn == "AlignRight")
                return Qt::AlignRight;
            else if(alignStrIn == "AlignTop")
                return Qt::AlignTop;
            else if(alignStrIn == "AlignBottom")
                return Qt::AlignBottom;
            else
                return Qt::AlignCenter;
        }

        QFont::Style strToQTTextStyle(QString textFontStyleStrIn)
        {
            if(textFontStyleStrIn == "StyleNormal")
                return QFont::StyleNormal;
            else if(textFontStyleStrIn == "StyleItalic")
                return QFont::StyleItalic;
            else
                return QFont::StyleOblique;
        }

        QFont::Weight strToQTTextWeight(QString textFontWeightStrIn)
        {
            if(textFontWeightStrIn == "Thin")
                return QFont::Thin;
            else if(textFontWeightStrIn == "Light")
                return QFont::Light;
            else if(textFontWeightStrIn == "Normal")
                return QFont::Normal;
            else
                return QFont::Bold;
        }


};


#endif // CANVAS_H
