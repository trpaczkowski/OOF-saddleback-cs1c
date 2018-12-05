#ifndef READFILE_H
#define READFILE_H

#include "shape.h"

#include <QObject>

#include <fstream>

#include <string>

//using namespace std;

class ReadFile
{
public:
    vector<Shape*> readShapeFile()
    {
        vector<Shape*> shapeVec;
        std::ifstream fin;

        fin.open("shape.txt");

        while(!fin.eof())
        {
            std::string identifierTrash; //Will read in identifier and take out ex: "ShapeType:"

            fin.ignore(10000, '\n'); //Removes empty line

            //Read ShapeID
            fin >> identifierTrash;
            int shapeIDNum;
            fin >> shapeIDNum;

            //Read shape type
            std::string shapeTypeStr;
            ShapeType shapeTypeEnum;

            fin >> identifierTrash;
            fin >> shapeTypeStr;

            //Find correct enum
            shapeTypeEnum = stringToShapeType(shapeTypeStr);

            //Seperate to different shape types
            switch(shapeTypeEnum)
            {
                //Line
            case ShapeType::LineType:
            {

                break;
            }
                //PolyLine
            case ShapeType::PolylineType:
            {
                break;
            }

                //Polygon
            case ShapeType::PolygonType:
            {
                break;
            }
                //Rectangle
            case ShapeType::RectangleType:
            {
                break;
            }
                //Square
            case ShapeType::SquareType:
            {
                break;
            }
                //Ellipse
            case ShapeType::EllipseType:
            {
                break;
            }
                //Circle
            case ShapeType::CircleType:
            {
                break;
            }
                //Text
            case ShapeType::NoShape:
            {
                break;
            }

            case ShapeType::TextType:
            {
                break;
            }
            default:{}
            }
        }
        fin.close();




        return shapeVec;
    }

private:
    ShapeType stringToShapeType(std::string shapeTypeStr)
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
};

#endif // READFILE_H
