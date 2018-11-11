/***********************************************************************
 * AUTHOR     : Jeffrey Adams
 * CLASS      : CS1C T/TH 12:30pm-2:50pm
 ***********************************************************************/
#ifndef PARSER_H
#define PARSER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <QString>
#include "vector.h"
#include "shape.h"
#include "string_util.h"

 using namespace shape::Shape;
 
 /***********************************************************************
 *  File: parser.h
 *  Description: Reads input file and creates shapes using the info 
 *  inside the input file.
 ***********************************************************************/
 
/***********************************************************************
 *  Draws shapes using QPainter. Shapes can be loaded from a file, added
 *  to a vector, manipulated and later saved. A login is required to
 *  access the program.
 ***********************************************************************/
 
class Parser
{	
public:
	
/******************************************
 * PUBLIC - PASER CLASS FUNCTIONS         *  
 ******************************************/
	
    //DEFAULT CONSTRUCTOR
    Parser() {}
	
    //DECONSTRUCTOR & CLOSES INPUT FILE
    ~Parser() {close();}

    //FUNCTION - CLOSES INPUT FILE
    void close();

    //FUNCTION - LOADS AND PARSES INPUT FILE & RETURNS TRUE IF SUCCESSFUL
    bool loadFile(const std::string& filePath);

    //FUNCTION - LOADS AND PARSES INPUT FILE & RETURNS TRUE IF SUCCESSFUL
    bool parse(Vector<Shape*>& shapeVector);

	
private:
	
/******************************************
 * PRIVATE - PASER CLASS SHAPEINFO STRUCT *  
 ******************************************/
	
    struct ShapeInfo
    {
	//FUNCTION - ASSIGNS INTIAL VALUES
        ShapeInfo()
        {
            //BRUSH VARIABLES
            brushStyle          = -1;
            
            //PEN VARIABLES
            penCapStyle         = -1;
            penJoinStyle        = -1;
            penStyle            = -1;
            penWidth            = -1;
            
            //SHAPE VARIABLES
            shapeDimensions     = nullptr;
            shapeDimensionCount = 0;
            shapeID             = -1;
            
            //TEXT VARIABLES
            textAlignment       = 0;
            textFontStyle       = -1;
            textFontWeight      = 0;
            textPointSize       = 0;
            
        } //END ShapeInfo()

	//FUNCTION - RESETS ALL VALUES BACK TO INITILIZATIONS
        void reset()
        {
            //BRUSH VARIABLES
            brushColor.clear();
            brushStyle          = -1;
            
            //PEN VARIABLES
            penCapStyle         = -1;
            penColor.clear();
            penJoinStyle        = -1;
            penStyle            = -1;
            penWidth            = -1;
            
            //SHAPE VARIABLES
            shapeDimensionCount = 0;
            shapeID             = -1;
            shapeType.clear();
            
            //TEXT VARIABLES
            textAlignment       = 0;
            textColor.clear();
            textFontFamily.clear();
            textFontStyle       = -1;
            textFontWeight      = 0;
            textPointSize       = 0;
            textString.clear();

            //ERROR CHECK
            if(shapeDimensions != nullptr)
            {
                delete[] shapeDimensions;
                shapeDimensions = nullptr;
                
            } //END if(shapeDimensions != nullptr)
            
        } //END void reset()

        //VARIABLES DEFINED IN SHAPEINFO STRUCT
        
        QString         brushColor;           // Variable defines brush color
        int             brushStyle;           // Variable defines brush style
        
        int             penCapStyle;          // Variable defines pen cap style
        QString         penColor;             // Variable defines pen color
        int             penJoinStyle;         // Variable defines pen joint style
        int             penStyle;             // Variable defines pen style
        int             penWidth;             // Variable defines pen width
        
        int*            shapeDimensions;      // Variable defines shape dimensions
        int             shapeDimensionCount;  // Variable defines dimension count
        int             shapeID;              // Variable defines shape ID
        QString         shapeType;            // Variable defines shape type
        
        int             textAlignment;        // Variable defines text alignment
        QString         textColor;            // Variable defines text color
        QString         textFontFamily;       // Variable defines text font family
        int             textFontStyle;        // Variable defines text font style
        int             textFontWeight;       // Variable defines text font weight
        int             textPointSize;        // Variable defines text point size
        QString         textString;           // Variable defines text string
        
    }; //END struct ShapeInfo

/******************************************
 * PRIVATE - PARSER CLASS FUNCTIONS       *  
 ******************************************/
	
    //FUNCTION - ADDS SHAPE TO SHAPE VECTOR
    void addShape(Vector<Shape*>& shapeVector);

    //FUNCTION - LOOKS FOR, EXTRACTS, & RETURNS "shapeDimensions" VALUE(S) 
    int* extractDimensions(const std::string& source, int& size, const std::string& line, size_t lineNumber);

    //FUNCTION - SETS THE VALUE OF AN INTEGER TO A STRING, IF THE STRING IS AN INTEGER
    bool setInteger(int& dest, const std::string& source) const;

    //FUNCTION - SETS A PART OF SHAPEINFO
    void setKeyValue(Vector<Shape*>& shapeVector, const std::string& key, const std::string& value,
                     const std::string& line, size_t lineNumber);

/******************************************
 * PRIVATE - PARSER CLASS VARIABLES       *  
 ******************************************/
	
    std::string                 mInputFilePath;  // Variable defines input file path
    std::ifstream               mInputFile;      // Variable defines input file
    std::vector<std::string>    mErrorList;      // Variable defines error list
    ShapeInfo                   mShapeInfo;      // Variable defines shape info
	
};

#endif
