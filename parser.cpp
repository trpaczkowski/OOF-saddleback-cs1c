/***********************************************************************
 * AUTHOR     : Jeffrey Adams
 * CLASS      : CS1C T/TH 12:30pm-2:50pm
 ***********************************************************************/
 #include "circle.h"
 #include "ellipse.h"
 #include "line.h"
 #include "parser.h"
 #include "polyline.h"
 #include "polygon.h"
 #include "rectangle.h"
 #include "textbox.h"
 #include "square.h"

 using namespace shape;

/***********************************************************************
 *  File: parser.cpp
 *  Description: Implementation to read input file and create shapes 
 *  using the info inside the input file.
 ***********************************************************************/

/***********************************************************************
 *  Draws shapes using QPainter. Shapes can be loaded from a file, added
 *  to a vector, manipulated and later saved. A login is required to
 *  access the program.
 ***********************************************************************/
 
 /********************
 * MEMBER FUNCTIONS *
 ********************/
 
//FUNCTION - CLOSES INPUT FILE
void Parser::close()
{
    if(mInputFile.is_open())
    {
        //CLOSES INPUT FILE
        mInputFile.close();
        
        //CLEARS FILE PATH
        mInputFilePath.clear();
        
        //CLEARS LIST
        mErrorList.clear();
    }
}

//FUNCTION - LOADS AND PARSES INPUT FILE & RETURNS TRUE IF SUCCESSFUL
bool Parser::loadFile(const std::string& filePath)
{
    //OPENS INPUT FILE
    mInputFile.open(filePath);
    
    //COPY FILE PATH INTO PRIVATE DATA PATH
    mInputFilePath = filePath;

    return mInputFile.is_open();
}

//FUNCTION - LOADS AND PARSES INPUT FILE & RETURNS TRUE IF SUCCESSFUL
bool Parser::parse(Vector<Shape*>& shapeVector)
{
    if(!mInputFile.is_open())
    {
        return false;
    }

    //LOCAL VARIABLES
    std::string inputLine;
    size_t lineNum = 1;

    while(std::getline(mInputFile, inputLine))
    {
        if(inputLine.empty())
        {
            //CLEARS INPUT LINE
            inputLine.clear();
         
            //INCREMENTS LINE NUMBER
            ++lineNum;
            continue;
        }
     
        //LOCAL VARIABLE
        size_t loc = inputLine.find(':');
     
        if(loc == std::string::npos)
        {
            mErrorList.push_back("Expected the format \"<key> : <value>\" (Line: " + std::to_string(lineNum) + " \"" + inputLine + "\")");
            inputLine.clear();
            ++lineNum;
            continue;
        }

        //LOCAL VARIABLES
        std::string key = trim_leading_ending(inputLine.substr(0, loc));
        std::string value = trim_leading_ending(inputLine.substr(loc + 1, inputLine.size() - loc - 1));

        //FUNCTION - SETS A PART OF SHAPEINFO
        setKeyValue(shapeVector, key, value, inputLine, lineNum);

        //CLEARS INPUT LINE
        inputLine.clear();
     
        //INCREMENTS LINE NUMBER
        ++lineNum;
    }

    if(mShapeInfo.shapeID != 0)
    {
        //FUNCTION - ADDS SHAPE TO SHAPE VECTOR
        addShape(shapeVector);
    }

    if(!mErrorList.empty())
    {
        //OUTPUT - NAME OF INPUT FILE
        std::cout << "In file " << mInputFilePath << ":" << std::endl;
     
        for(std::vector<std::string>::iterator it = mErrorList.begin(); it != mErrorList.end(); ++it)
        {
            std::cout << "\t" << *it << std::endl;
        }
        return false;
    }
 
    //PROCESSING - SELECTION SORT
    selection_sort(shapeVector.begin(), shapeVector.end(), [](Shape* s1, Shape* s2) {return s1->getID() > s2->getID(); });
    return true;
}

/********************
 * HELPER FUNCTIONS *
 ********************/

 //FUNCTION - ADDS SHAPE TO SHAPE VECTOR
 void Parser::addShape(Vector<Shape*>& shapeVector)
 {
    if(mShapeInfo.shapeType == "Line")
    {
        //ALLOCATING NEW MEMORY
        Line* line = new Line();
     
        //LOCAL VARIABLE
        QPen pen;

        //PROCESSING - SETS VALUES FOR PEN
        pen.setColor(QColor(mShapeInfo.penColor));
        pen.setWidth(mShapeInfo.penWidth);
        pen.setStyle(static_cast<Qt::PenStyle>(mShapeInfo.penStyle));
        pen.setCapStyle(static_cast<Qt::PenCapStyle>(mShapeInfo.penCapStyle));
        pen.setJoinStyle(static_cast<Qt::PenJoinStyle>(mShapeInfo.penJoinStyle));

        //PROCESSING - SETS VALUES FOR LINE
        line->setID(mShapeInfo.shapeID);
        line->setPoints(mShapeInfo.shapeDimensions[0], mShapeInfo.shapeDimensions[1],
            mShapeInfo.shapeDimensions[2], mShapeInfo.shapeDimensions[3]);
        line->setPen(pen);

        //PROCESSING - ADDS A NEW ELEMENT TO THE END OF THE VECTOR
        shapeVector.push_back(line);
    }
    else if(mShapeInfo.shapeType == "Polyline")
    {
        //ALLOCATING NEW MEMORY
        Polyline* polyline = new Polyline();
     
        //LOCAL VARIABLE
        QPen pen;

        //PROCESSING - SETS VALUES FOR PEN
        pen.setColor(QColor(mShapeInfo.penColor));
        pen.setWidth(mShapeInfo.penWidth);
        pen.setStyle(static_cast<Qt::PenStyle>(mShapeInfo.penStyle));
        pen.setCapStyle(static_cast<Qt::PenCapStyle>(mShapeInfo.penCapStyle));
        pen.setJoinStyle(static_cast<Qt::PenJoinStyle>(mShapeInfo.penJoinStyle));

        //PROCESSING - SETS VALUES FOR POLYLINE
        polyline->setID(mShapeInfo.shapeID);
        polyline->setPointData(mShapeInfo.shapeDimensions, mShapeInfo.shapeDimensionCount / 2);
        polyline->setPen(pen);

        //PROCESSING - ADDS A NEW ELEMENT TO THE END OF THE VECTOR
        shapeVector.push_back(polyline);
    }
    else if(mShapeInfo.shapeType == "Polygon")
    {
        //ALLOCATING NEW MEMORY
        Polygon* polygon = new Polygon();
     
        //LOCAL VARIABLES
        QPen   pen;
        QBrush brush;

        //PROCESSING - SETS VALUES FOR PEN
        pen.setColor(QColor(mShapeInfo.penColor));
        pen.setWidth(mShapeInfo.penWidth);
        pen.setStyle(static_cast<Qt::PenStyle>(mShapeInfo.penStyle));
        pen.setCapStyle(static_cast<Qt::PenCapStyle>(mShapeInfo.penCapStyle));
        pen.setJoinStyle(static_cast<Qt::PenJoinStyle>(mShapeInfo.penJoinStyle));

        brush.setColor(QColor(mShapeInfo.brushColor));
        brush.setStyle(static_cast<Qt::BrushStyle>(mShapeInfo.brushStyle));

        //PROCESSING - SETS VALUES FOR POLYGON
        polygon->setID(mShapeInfo.shapeID);
        polygon->setPointData(mShapeInfo.shapeDimensions, mShapeInfo.shapeDimensionCount / 2);
        polygon->setPen(pen);
        polygon->setBrush(brush);

        //PROCESSING - ADDS A NEW ELEMENT TO THE END OF THE VECTOR
        shapeVector.push_back(polygon);
    }
    else if(mShapeInfo.shapeType == "Rectangle")
    {
        //ALLOCATING NEW MEMORY
        Rectangle* rectangle = new Rectangle();
     
        //LOCAL VARIABLES
        QPen   pen;
        QBrush brush;

        //PROCESSING - SETS VALUES FOR PEN
        pen.setColor(QColor(mShapeInfo.penColor));
        pen.setWidth(mShapeInfo.penWidth);
        pen.setStyle(static_cast<Qt::PenStyle>(mShapeInfo.penStyle));
        pen.setCapStyle(static_cast<Qt::PenCapStyle>(mShapeInfo.penCapStyle));
        pen.setJoinStyle(static_cast<Qt::PenJoinStyle>(mShapeInfo.penJoinStyle));

        //PROCESSING - SETS VALUES FOR BRUSH
        brush.setColor(QColor(mShapeInfo.brushColor));
        brush.setStyle(static_cast<Qt::BrushStyle>(mShapeInfo.brushStyle));

        //PROCESSING - SETS VALUES FOR RECTANGLE
        rectangle->setID(mShapeInfo.shapeID);
        rectangle->setPosition(mShapeInfo.shapeDimensions[0], mShapeInfo.shapeDimensions[1]);
        rectangle->setDimensions(mShapeInfo.shapeDimensions[2], mShapeInfo.shapeDimensions[3]);
        rectangle->setPen(pen);
        rectangle->setBrush(brush);

        //PROCESSING - ADDS A NEW ELEMENT TO THE END OF THE VECTOR
        shapeVector.push_back(rectangle);
    }
    else if(mShapeInfo.shapeType == "Square")
    {
        //ALLOCATING NEW MEMORY
        Square* square = new Square();
     
        //LOCAL VARIABLES
        QPen   pen;
        QBrush brush;

        //PROCESSING - SETS VALUES FOR PEN
        pen.setColor(QColor(mShapeInfo.penColor));
        pen.setWidth(mShapeInfo.penWidth);
        pen.setStyle(static_cast<Qt::PenStyle>(mShapeInfo.penStyle));
        pen.setCapStyle(static_cast<Qt::PenCapStyle>(mShapeInfo.penCapStyle));
        pen.setJoinStyle(static_cast<Qt::PenJoinStyle>(mShapeInfo.penJoinStyle));

        //PROCESSING - SETS VALUES FOR BRUSH
        brush.setColor(QColor(mShapeInfo.brushColor));
        brush.setStyle(static_cast<Qt::BrushStyle>(mShapeInfo.brushStyle));

        //PROCESSING - SETS VALUES FOR SQUARE
        square->setID(mShapeInfo.shapeID);
        square->setPosition(mShapeInfo.shapeDimensions[0], mShapeInfo.shapeDimensions[1]);
        square->setSide(mShapeInfo.shapeDimensions[2]);
        square->setPen(pen);
        square->setBrush(brush);

        //PROCESSING - ADDS A NEW ELEMENT TO THE END OF THE VECTOR
        shapeVector.push_back(square);
    }
    else if(mShapeInfo.shapeType == "Ellipse")
    {
        //ALLOCATING NEW MEMORY
        Ellipse* ellipse = new Ellipse();
     
        //LOCAL VARIABLES
        QPen   pen;
        QBrush brush;

        //PROCESSING - SETS VALUES FOR PEN
        pen.setColor(QColor(mShapeInfo.penColor));
        pen.setWidth(mShapeInfo.penWidth);
        pen.setStyle(static_cast<Qt::PenStyle>(mShapeInfo.penStyle));
        pen.setCapStyle(static_cast<Qt::PenCapStyle>(mShapeInfo.penCapStyle));
        pen.setJoinStyle(static_cast<Qt::PenJoinStyle>(mShapeInfo.penJoinStyle));

        //PROCESSING - SETS VALUES FOR BRUSH
        brush.setColor(QColor(mShapeInfo.brushColor));
        brush.setStyle(static_cast<Qt::BrushStyle>(mShapeInfo.brushStyle));

        //PROCESSING - SETS VALUES FOR ELLIPSE
        ellipse->setID(mShapeInfo.shapeID);
        ellipse->setPosition(mShapeInfo.shapeDimensions[0], mShapeInfo.shapeDimensions[1]);
        ellipse->setRadii(mShapeInfo.shapeDimensions[2], mShapeInfo.shapeDimensions[3]);
        ellipse->setPen(pen);
        ellipse->setBrush(brush);

        //PROCESSING - ADDS A NEW ELEMENT TO THE END OF THE VECTOR
        shapeVector.push_back(ellipse);
    }
    else if(mShapeInfo.shapeType == "Circle")
    {
        //ALLOCATING NEW MEMORY
        Circle* circle = new Circle();
     
        //LOCAL VARIABLES
        QPen    pen;
        QBrush  brush;

        //PROCESSING - SETS VALUES FOR PEN
        pen.setColor(QColor(mShapeInfo.penColor));
        pen.setWidth(mShapeInfo.penWidth);
        pen.setStyle(static_cast<Qt::PenStyle>(mShapeInfo.penStyle));
        pen.setCapStyle(static_cast<Qt::PenCapStyle>(mShapeInfo.penCapStyle));
        pen.setJoinStyle(static_cast<Qt::PenJoinStyle>(mShapeInfo.penJoinStyle));

        //PROCESSING - SETS VALUES FOR BRUSH
        brush.setColor(QColor(mShapeInfo.brushColor));
        brush.setStyle(static_cast<Qt::BrushStyle>(mShapeInfo.brushStyle));

        //PROCESSING - SETS VALUES FOR CIRCLE
        circle->setID(mShapeInfo.shapeID);
        circle->setPosition(mShapeInfo.shapeDimensions[0], mShapeInfo.shapeDimensions[1]);
        circle->setRadius(mShapeInfo.shapeDimensions[2]);
        circle->setPen(pen);
        circle->setBrush(brush);

        //PROCESSING - ADDS A NEW ELEMENT TO THE END OF THE VECTOR
        shapeVector.push_back(circle);
    }
    else if(mShapeInfo.shapeType == "Text")
    {
        //ALLOCATING NEW MEMORY
        TextBox* text = new TextBox();
     
        //LOCAL VARIABLES
        QPen  pen;
        QFont font;

        //PROCESSING - SETS COLOR FOR PEN
        pen.setColor(QColor(mShapeInfo.textColor));

        //PROCESSING - SETS VALUES FOR FONT
        font.setPointSize(mShapeInfo.textPointSize);
        font.setFamily(mShapeInfo.textFontFamily);
        font.setStyle(static_cast<QFont::Style>(mShapeInfo.textFontStyle));
        font.setWeight(mShapeInfo.textFontWeight);

        //PROCESSING - SETS VALUES FOR ELLIPSE
        text->setID(mShapeInfo.shapeID);
        text->setPosition(mShapeInfo.shapeDimensions[0], mShapeInfo.shapeDimensions[1]);
        text->setDimensions(mShapeInfo.shapeDimensions[2], mShapeInfo.shapeDimensions[3]);
        text->setText(mShapeInfo.textString);
        text->setAlignment(static_cast<Qt::AlignmentFlag>(mShapeInfo.textAlignment));
        text->setPen(pen);
        text->setFont(font);

        //PROCESSING - ADDS A NEW ELEMENT TO THE END OF THE VECTOR
        shapeVector.push_back(text);
    }
    else
    {
        //ERROR CHECK - INVALID SHAPE TYPE
        mErrorList.push_back("Missing shape type. (Shape Creator [ShapeID = " + std::to_string(mShapeInfo.shapeID) + "])");
    }
 }

//FUNCTION - LOOKS FOR, EXTRACTS, & RETURNS "shapeDimensions" VALUE(S)
int* Parser::extractDimensions(const std::string& source, int& size, const std::string& line, size_t lineNumber)
{
    std::string value;
    size_t low = 0;
    size_t i = 0;
    int* dest = nullptr;
    int* tmp = nullptr;

    for(; i < source.length(); ++i)
    {
        if(std::isdigit(source[i]))
        {
            continue;
        }
        else if(source[i] == ',')
        {
            value = source.substr(low, i - low);

            if(dest != nullptr)
            {
                tmp = dest;
                dest = new int[size + 1];

                for(int j = 0; j < size; ++j)
                    dest[j] = tmp[j];
                delete[] tmp;
                dest[size] = std::stoi(value);
                low = i + 1;
                ++size;
            }
            else
            {
                dest = new int[1];
                dest[0] = std::stoi(value);
                low = i + 1;
                size = 1;
            }
        }
        else
        {
            mErrorList.push_back("Unexpected character (Line: " + std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }

    //INSERT FINAL VALUE
    value = source.substr(low, i - low);
    tmp   = dest;
 
    //ALLOCATING NEW MEMORY
    dest = new int[size + 1];

    for(int j = 0; j < size; ++j)
    {
        dest[j] = tmp[j];
    }
 
    delete[] tmp;
    dest[size] = std::stoi(value);
    ++size;

    return dest;
}

//FUNCTION - SETS THE VALUE OF AN INTEGER TO A STRING, IF THE STRING IS AN INTEGER
bool Parser::setInteger(int& dest, const std::string& source) const
{
    for(size_t i = 0; i < source.length(); ++i)
    {
        if(!std::isdigit(source[i]))
        {
            return false;
        }
    }

    dest = std::stoi(source);
    return true;
}

//FUNCTION - SETS A PART OF SHAPEINFO
void Parser::setKeyValue(Vector<Shape*>& shapeVector, const std::string& key, const std::string& value, const std::string& line, size_t lineNumber)
{
    if(key == "BrushColor")
    {
        if((value == "white"  ) ||
           (value == "black"  ) ||
           (value == "red"    ) ||
           (value == "green"  ) ||
           (value == "blue"   ) ||
           (value == "cyan"   ) ||
           (value == "magenta") ||
           (value == "yellow" ) ||
           (value == "gray"   ))
        {
            //PROCESSING - SETS BRUSH COLOR
            mShapeInfo.brushColor = QString::fromStdString(value);
        }
        else
        {
            //ERROR CHECK - UNEXPECTED BRUSH COLOR
            mErrorList.push_back("Unexpected value. Try \"white\", \"black\", \"red\", \"green\", \"blue\", \"cyan\", \"magenta\", " +
                                 std::string("\"yellow\", or \"gray\" (Line: ") + std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }
    else if(key == "BrushStyle")
    {
        if(value == "NoBrush")
        {
            //PROCESSING - SETS BRUSH STYLE
            mShapeInfo.brushStyle = Qt::NoBrush;
        }
        else if(value == "SolidPattern")
        {
            //PROCESSING - SETS BRUSH STYLE
            mShapeInfo.brushStyle = Qt::SolidPattern;
        }
        else if(value == "HorPattern")
        {
            //PROCESSING - SETS BRUSH STYLE
            mShapeInfo.brushStyle = Qt::HorPattern;
        }
        else if(value == "VerPattern")
        {
            //PROCESSING - SETS BRUSH STYLE
            mShapeInfo.brushStyle = Qt::VerPattern;
        }
        else
        {
            //ERROR CHECK - UNEXPECTED BRUSH STYLE
            mErrorList.push_back("Unexpected value. Try \"NoBrush\", \"SolidPattern\", \"HorPattern\", or \"VerPattern\" (Line: " +
                std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }
    else if(key == "PenCapStyle")
    {
        if(value == "SquareCap")
        {
            //PROCESSING - SETS PEN CAP STYLE
            mShapeInfo.penCapStyle = Qt::SquareCap;
        }
        else if(value == "FlatCap")
        {
            //PROCESSING - SETS PEN CAP STYLE
            mShapeInfo.penCapStyle = Qt::FlatCap;
        }
        else if(value == "RoundCap")
        {
            //PROCESSING - SETS PEN CAP STYLE
            mShapeInfo.penCapStyle = Qt::RoundCap;
        }
        else
        {
            //ERROR CHECK - UNEXPECTED PEN CAP STYLE
            mErrorList.push_back("Unexpected value. Try \"SquareCap\", \"FlatCap\", or \"RoundCap\" (Line: " +
                std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }
    else if(key == "PenColor")
    {
        //PROCESSING - SETS PEN COLOR
        mShapeInfo.penColor = QString::fromStdString(value);
    }
    else if(key == "PenJoinStyle")
    {
        if(value == "MiterJoin")
        {
            //PROCESSING - SETS PEN JOINT STYLE
            mShapeInfo.penJoinStyle = Qt::MiterJoin;
        }
        else if(value == "BevelJoin")
        {
            //PROCESSING - SETS PEN JOINT STYLE
            mShapeInfo.penJoinStyle = Qt::BevelJoin;
        }
        else if(value == "RoundJoin")
        {
            //PROCESSING - SETS PEN JOINT STYLE
            mShapeInfo.penJoinStyle = Qt::RoundJoin;
        }
        else
        {
            //ERROR CHECK - UNEXPECTED PEN JOINT STYLE
            mErrorList.push_back("Unexpected value. Try \"MiterJoin\", \"BevelJoin\", or \"RoundJoin\" (Line: " +
                std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }
    else if(key == "PenStyle")
    {
        if(value == "SolidLine")
        {
            //PROCESSING - SETS PEN STYLE
            mShapeInfo.penStyle = Qt::SolidLine;
        }
        else if(value == "DashLine")
        {
            //PROCESSING - SETS PEN STYLE
            mShapeInfo.penStyle = Qt::DashLine;
        }
        else if(value == "DotLine")
        {
            //PROCESSING - SETS PEN STYLE
            mShapeInfo.penStyle = Qt::DotLine;
        }
        else if(value == "DashDotLine")
        {
            //PROCESSING - SETS PEN STYLE
            mShapeInfo.penStyle = Qt::DashDotLine;
        }
        else if(value == "DashDotDotLine")
        {
            //PROCESSING - SETS PEN STYLE
            mShapeInfo.penStyle = Qt::DashDotDotLine;
        }
        else
        {
            //ERROR CHECK - UNEXPECTED PEN STYLE
            mErrorList.push_back("Unexpected value. Try \"SolidLine\", \"DashLine\", \"DotLine\", \"DashDotLine\", or " +
                std::string("\"DashDotDotLine\" (Line: ") + std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }
    else if(key == "PenWidth")
    {
        if(setInteger(mShapeInfo.penWidth, value))
        {
            if(mShapeInfo.penWidth < 0 || mShapeInfo.penWidth > 20)
            {
                //ERROR CHECK - UNEXPECTED PEN WIDTH
                mErrorList.push_back("Must be an integer between 0 and 20, inclusive (Line: " + std::to_string(lineNumber) +
                                     " \"" + line + "\")");
                //PROCESSING - RE-INITIALIZES PEN WIDTH
                mShapeInfo.penWidth = -1;
            }
        }
        else
        {
            //ERROR CHECK - UNEXPECTED VALUE
            mErrorList.push_back("Expected integer (Line: " + std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }
    else if(key == "ShapeDimensions")
    {
        //LOCAL VARIABLE
        int* array = nullptr;

        if(mShapeInfo.shapeType == "Line")
        {
           //FUNCTION - LOOKS FOR, EXTRACTS, & RETURNS "shapeDimensions" VALUE(S) 
           array = extractDimensions(trim_whitespace(value), mShapeInfo.shapeDimensionCount, line, lineNumber);
         
           if(mShapeInfo.shapeDimensionCount == 4)
           {
               //PROCESSING - SETS SHAPE DIMENSIONS
               mShapeInfo.shapeDimensions = array;
           }
           else
           {
               //ERROR CHECK - UNEXPECTED # OF VALUES
               mErrorList.push_back("Expected four values [x1, y1, x2, y2] (Line: " +
                   std::to_string(lineNumber) + " \"" + line + "\")");
           }
        }
        else if(mShapeInfo.shapeType == "Polyline")
        {
            //FUNCTION - LOOKS FOR, EXTRACTS, & RETURNS "shapeDimensions" VALUE(S) 
            array = extractDimensions(trim_whitespace(value), mShapeInfo.shapeDimensionCount, line, lineNumber);
         
            if(!(mShapeInfo.shapeDimensionCount % 2))
            {
                //PROCESSING - SETS SHAPE DIMENSIONS
                mShapeInfo.shapeDimensions = array;
            }
            else
            {
                //ERROR CHECK - UNEXPECTED # OF VALUES
                mErrorList.push_back("Odd number of values. Expected coordinates pairs. [x1, y1, x2, y2, ...] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
            }
        }
        else if(mShapeInfo.shapeType == "Polygon")
        {
            //FUNCTION - LOOKS FOR, EXTRACTS, & RETURNS "shapeDimensions" VALUE(S) 
            array = extractDimensions(trim_whitespace(value), mShapeInfo.shapeDimensionCount, line, lineNumber);
         
            if(!(mShapeInfo.shapeDimensionCount % 2))
            {
                //PROCESSING - SETS SHAPE DIMENSIONS
                mShapeInfo.shapeDimensions = array;
            }
            else
            {
                //ERROR CHECK - UNEXPECTED # OF VALUES
                mErrorList.push_back("Odd number of values. Expected coordinates pairs. [x1, y1, x2, y2, ...] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
            }
        }
        else if(mShapeInfo.shapeType == "Rectangle")
        {
            //FUNCTION - LOOKS FOR, EXTRACTS, & RETURNS "shapeDimensions" VALUE(S) 
            array = extractDimensions(trim_whitespace(value), mShapeInfo.shapeDimensionCount, line, lineNumber);
         
            if(mShapeInfo.shapeDimensionCount == 4)
            {
                //PROCESSING - SETS SHAPE DIMENSIONS
                mShapeInfo.shapeDimensions = array;
            }
            else
            {
                //ERROR CHECK - UNEXPECTED # OF VALUES
                mErrorList.push_back("Expected four values [x, y, width, height] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
            }
        }
        else if(mShapeInfo.shapeType == "Square")
        {
            //FUNCTION - LOOKS FOR, EXTRACTS, & RETURNS "shapeDimensions" VALUE(S) 
            array = extractDimensions(trim_whitespace(value), mShapeInfo.shapeDimensionCount, line, lineNumber);
         
            if(mShapeInfo.shapeDimensionCount == 3)
            {
                //PROCESSING - SETS SHAPE DIMENSIONS
                mShapeInfo.shapeDimensions = array;
            }
            else
            {
                //ERROR CHECK - UNEXPECTED # OF VALUES
                mErrorList.push_back("Expected three values [x, y, side] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
            }
        }
        else if(mShapeInfo.shapeType == "Circle")
        {
            //FUNCTION - LOOKS FOR, EXTRACTS, & RETURNS "shapeDimensions" VALUE(S) 
            array = extractDimensions(trim_whitespace(value), mShapeInfo.shapeDimensionCount, line, lineNumber);
         
            if(mShapeInfo.shapeDimensionCount == 3)
            {
                //PROCESSING - SETS SHAPE DIMENSIONS
                mShapeInfo.shapeDimensions = array;
            }
            else
            {
                //ERROR CHECK - UNEXPECTED # OF VALUES
                mErrorList.push_back("Expected three values [x, y, radius] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
            }
        }
        else if(mShapeInfo.shapeType == "Ellipse")
        {
            //FUNCTION - LOOKS FOR, EXTRACTS, & RETURNS "shapeDimensions" VALUE(S) 
            array = extractDimensions(trim_whitespace(value), mShapeInfo.shapeDimensionCount, line, lineNumber);
         
            if(mShapeInfo.shapeDimensionCount == 4)
            {
                //PROCESSING - SETS SHAPE DIMENSIONS
                mShapeInfo.shapeDimensions = array;
            }
            else
            {
                //ERROR CHECK - UNEXPECTED # OF VALUES
                mErrorList.push_back("Expected three values [x, y, rx, ry] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
            }
        }
        else if(mShapeInfo.shapeType == "Text")
        {
            //FUNCTION - LOOKS FOR, EXTRACTS, & RETURNS "shapeDimensions" VALUE(S) 
            array = extractDimensions(trim_whitespace(value), mShapeInfo.shapeDimensionCount, line, lineNumber);
         
            if(mShapeInfo.shapeDimensionCount == 4)
            {
                //PROCESSING - SETS SHAPE DIMENSIONS
                mShapeInfo.shapeDimensions = array;
            }
            else
            {
                //ERROR CHECK - UNEXPECTED # OF VALUES
                mErrorList.push_back("Expected four values [x, y, width, height] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
            }
        }
        else
        {
            //ERROR CHECK - UNEXPECTED # OF VALUES
            mErrorList.push_back("Shape type needs to be defined before defining dimensions (Line: " +
                std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }
    else if(key == "ShapeId")
    {
        if(mShapeInfo.shapeID > 0)
        {
            //FUNCTION - ADDS SHAPE TO SHAPE VECTOR
            addShape(shapeVector);
         
            //FUNCTION - RESETS ALL VALUES BACK TO INITILIZATIONS
            mShapeInfo.reset();
        }

        if(!setInteger(mShapeInfo.shapeID, value))
        {
            //ERROR CHECK - UNEXPECTED VALUE
            mErrorList.push_back("Expected integer (Line: " + std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }
    else if(key == "ShapeType")
    {
        if((value == "Line"     ) ||
           (value == "Polyline" ) ||
           (value == "Polygon"  ) ||
           (value == "Rectangle") ||
           (value == "Square"   ) ||
           (value == "Circle"   ) ||
           (value == "Ellipse"  ) ||
           (value == "Text"     ))
        {
            //PROCESSING - SETS SHAPE TYPE
            mShapeInfo.shapeType = QString::fromStdString(value);
        }
        else
        {
            //ERROR CHECK - UNEXPECTED SHAPE TYPE
            mErrorList.push_back("Unexpected value. Try \"Line\", \"Polyline\", \"Polygon\", \"Rectangle\", \"Square\", \"Circle\", " +
                std::string("\"Ellipse\", \"Text\" (Line: ") + std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }
    else if(key == "TextAlignment")
    {
        if(value == "AlignLeft")
        {
            //PROCESSING - SETS TEXT ALIGNMENT
            mShapeInfo.textAlignment |= Qt::AlignLeft;
        }
        else if(value == "AlignRight")
        {
            //PROCESSING - SETS TEXT ALIGNMENT
            mShapeInfo.textAlignment |= Qt::AlignRight;
        }
        else if(value == "AlignRight")
        {
            //PROCESSING - SETS TEXT ALIGNMENT
            mShapeInfo.textAlignment |= Qt::AlignTop;
        }
        else if(value == "AlignBottom")
        {
            //PROCESSING - SETS TEXT ALIGNMENT
            mShapeInfo.textAlignment |= Qt::AlignBottom;
        }
        else if(value == "AlignCenter")
        {
            //PROCESSING - SETS TEXT ALIGNMENT
            mShapeInfo.textAlignment |= Qt::AlignCenter;
        }
        else
        {
            //ERROR CHECK - UNEXPECTED TEXT ALIGNMENT
            mErrorList.push_back("Unexpected value. Try \"AlignLeft\", \"AlignRight\", \"AlignTop\", \"AlignBottom\", or " +
                std::string("\"AlignCenter\" (Line: ") + std::to_string(lineNumber) + " \"" + line + "\")");
        }

    }
    else if(key == "TextColor")
    {
        if((value == "white"  ) ||
           (value == "black"  ) ||
           (value == "red"    ) ||
           (value == "green"  ) ||
           (value == "blue"   ) ||
           (value == "cyan"   ) ||
           (value == "magenta") ||
           (value == "yellow" ) ||
           (value == "gray"   ))
        {
            //PROCESSING - SETS TEXT COLOR
            mShapeInfo.textColor = QString::fromStdString(value);
        }
        else
        {
            //ERROR CHECK - UNEXPECTED TEXT COLOR
            mErrorList.push_back("Unexpected value. Try \"white\", \"black\", \"red\", \"green\", \"blue\", \"cyan\", \"magenta\", " +
                std::string("\"yellow\", or \"gray\" (Line: ") + std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }
    else if(key == "TextFontFamily")
    {
        if((value == "Comic Sans MS") ||
           (value == "Courier"      ) ||
           (value == "Helvetica"    ) ||
           (value == "Times"        ))
        {
            //PROCESSING - SETS TEXT COLOR
            mShapeInfo.textFontFamily = QString::fromStdString(value);
        }
        else
        {
            //ERROR CHECK - UNEXPECTED TEXT COLOR
            mErrorList.push_back("Unexpected value. Try \"Courier Sans MS\", \"Courier\", \"Helvetica\", or \"Times\" (Line: " +
                std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }
    else if(key == "TextFontStyle")
    {
        if(value == "StyleNormal")
        {
            //PROCESSING - SETS TEXT FONT STYLE
            mShapeInfo.textFontStyle = QFont::StyleNormal;
        }
        else if(value == "StyleItalic")
        {
            //PROCESSING - SETS TEXT FONT STYLE
            mShapeInfo.textFontStyle = QFont::StyleItalic;
        }
        else if(value == "StyleOblique")
        {
            //PROCESSING - SETS TEXT FONT STYLE
            mShapeInfo.textFontStyle = QFont::StyleOblique;
        }
        else
        {
            //ERROR CHECK - UNEXPECTED TEXT FONT STYLE
            mErrorList.push_back("Unexpected value. Try \"StyleNormal\", \"StyleItalic\", or \"StyleOblique\" (Line: " +
                std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }
    else if(key == "TextFontWeight")
    {
        if(value == "Thin")
        {
            //PROCESSING - SETS TEXT FONT WEIGHT
            mShapeInfo.textFontWeight = QFont::Thin;
        }
        else if(value == "Light")
        {
            //PROCESSING - SETS TEXT FONT WEIGHT
            mShapeInfo.textFontWeight = QFont::Light;
        }
        else if(value == "Normal")
        {
            //PROCESSING - SETS TEXT FONT WEIGHT
            mShapeInfo.textFontWeight = QFont::Normal;
        }
        else if(value == "Bold")
        {
            //PROCESSING - SETS TEXT FONT WEIGHT
            mShapeInfo.textFontWeight = QFont::Bold;
        }
        else
        {
            //ERROR CHECK - UNEXPECTED TEXT FONT WEIGHT
            mErrorList.push_back("Unexpected value. Try \"Thin\", \"Light\", \"Normal\", or \"Bold\" (Line: " +
                std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }
    else if(key == "TextPointSize")
    {
        //FUNCTION - SETS THE VALUE OF AN INTEGER TO A STRING, IF THE STRING IS AN INTEGER
        if(setInteger(mShapeInfo.textPointSize, value))
        {
            if(mShapeInfo.textPointSize <= 0 || mShapeInfo.textPointSize > 50)
            {
                //ERROR CHECK - UNEXPECTED TEXT POINT SIZE
                mErrorList.push_back("Must be an integer greater than 0 and less than or equal to 50 (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
             
                //RE-INITIALIZATION
                mShapeInfo.penWidth = -1;
            }
        }
        else
        {
            //ERROR CHECK - UNEXPECTED VALUE
            mErrorList.push_back("Expected integer (Line: " + std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }
    else if(key == "TextString")
    {
        //PROCESSING - SETS TEXT STRING
        mShapeInfo.textString = QString::fromStdString(value);
    }
    else
    {
        //ERROR CHECK - UNEXPECTED VALUE
        mErrorList.push_back("Unexpected key (Line: " + std::to_string(lineNumber) + " \"" + line + "\")");
    }
}
