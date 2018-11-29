#include "dialog.h"
#include <QMessageBox>
#include <QtGui>
#include <QIntValidator>
#include <iostream>
#include <QFont>
#include "renderarea.h"


/**************************************************
 * RemoveShapeDialog
 **************************************************/
RemoveShapeDialog::RemoveShapeDialog(QWidget *parent) : QDialog(parent)
{
    exited = false;
    submit = new QPushButton("Remove");
    connect(submit, SIGNAL(clicked(bool)), this, SLOT(setRemoveId()));
    input = new QLineEdit();
    input->setPlaceholderText("Enter id here");
    input->setValidator(new QIntValidator(this));
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(input);
    layout->addWidget(submit);\
    setLayout(layout);
    setWindowTitle("Remove Shape");
}
/**
 * @brief Sets the remove info for the specified shape, which
 * then gets sent to the render area.
 */
void RemoveShapeDialog::setRemoveId()
{
    if (input->text() == "")
    {
        QMessageBox box;
        box.setText("Enter an id!");
        box.exec();
    }
    else
    {  
        removeId = input->text().toInt();
        this->close();
    }
}
void RemoveShapeDialog::reject()
{
    exited = true;
    QDialog::reject();
}

/**************************************************
 * MoveShapeDialog
 **************************************************/

MoveShapeDialog::MoveShapeDialog(QWidget *parent) :QDialog(parent)
{
    exited = false;
    submit = new QPushButton("Move");
    connect(submit, SIGNAL(clicked(bool)), this, SLOT(setMoveInfo()));
    idInput = new QLineEdit();
    xInput = new QLineEdit();
    yInput = new QLineEdit();
    idInput->setValidator(new QIntValidator(this));
    xInput->setValidator(new QIntValidator(this));
    yInput->setValidator(new QIntValidator(this));
    QFormLayout* layout = new QFormLayout();
    layout->addRow("ID: ", idInput);
    layout->addRow("X Coord: ", xInput);
    layout->addRow("Y Coord: ", yInput);
    layout->addRow(" ", submit);
    setLayout(layout);
    setWindowTitle("Move Shape");
}

/**
 * @brief Sets the move info for the specified shape, which
 * then gets sent to the render area.
 */
void MoveShapeDialog::setMoveInfo()
{
    if (idInput->text() == "" || xInput->text() == ""
            || yInput->text() == "")
    {
        QMessageBox q;
        q.setText("Incomplete fields!");
        q.exec();
    }
    else
    {
        moveId = idInput->text().toInt();
        x_move = xInput->text().toInt();
        y_move = yInput->text().toInt();
        this->close();
    }
}
void MoveShapeDialog::reject()
{
    exited = true;
    QDialog::reject();
}

/**************************************************
 * AddShapeDialog
 **************************************************/

AddShapeDialog::AddShapeDialog(QWidget *parent) : QDialog(parent)
{
    formLayout = new QFormLayout();
    shapeTypeInput = new QComboBox();
    shapeTypeInput->addItem("Line");
    shapeTypeInput->addItem("Polyline");
    shapeTypeInput->addItem("Polygon");
    shapeTypeInput->addItem("Rectangle");
    shapeTypeInput->addItem("Ellipse");
    shapeTypeInput->addItem("Circle");
    shapeTypeInput->addItem("Text");
    connect(shapeTypeInput, SIGNAL(currentIndexChanged(int)), this, SLOT(onShapeTypeSelected()));
    shapeTypeInput->setCurrentIndex(0);
    formLayout->addRow("Select Shape: ", shapeTypeInput);
    setLayout(formLayout);
    setWindowTitle("Add a new Shape");

    //default is to create a new Line
    shape = new Line(this, 0);
    initLineControls();
}
void AddShapeDialog::initLineControls()
{
    lineFirstXPointInput = new QLineEdit();
    lineFirstYPointInput = new QLineEdit();
    lineSecondXPointInput = new QLineEdit();
    lineSecondYPointInput = new QLineEdit();
    lineFirstXPointInput->setValidator(new QIntValidator(this));
    lineFirstYPointInput->setValidator(new QIntValidator(this));
    lineSecondXPointInput->setValidator(new QIntValidator(this));
    lineSecondYPointInput->setValidator(new QIntValidator(this));
    formLayout->addRow("Begin X: ", lineFirstXPointInput);
    formLayout->addRow("Begin Y: ", lineFirstYPointInput);
    formLayout->addRow("End X: ", lineSecondXPointInput);
    formLayout->addRow("End Y: ", lineSecondYPointInput);

    penColorInput = new QComboBox();
    penColorInput->addItem("Blue");
    penColorInput->addItem("Red");
    penColorInput->addItem("Cyan");
    penColorInput->addItem("Green");
    penColorInput->addItem("Yellow");
    penColorInput->addItem("Magenta");
    penColorInput->addItem("Black");

    penWidthInput = new QSpinBox();
    penWidthInput->setRange(0,20);

    penStyleInput = new QComboBox();
    penStyleInput->addItem("SolidLine", static_cast<int>(Qt::SolidLine));
    penStyleInput->addItem("DashLine", static_cast<int>(Qt::DashLine));
    penStyleInput->addItem("DashDotLine", static_cast<int>(Qt::DashDotLine));
    penStyleInput->addItem("DashDotDotLine", static_cast<int>(Qt::DashDotDotLine));

    penCapInput = new QComboBox();
    penCapInput->addItem("SquareCap", Qt::SquareCap);
    penCapInput->addItem("FlatCap", Qt::FlatCap);
    penCapInput->addItem("RoundCap", Qt::RoundCap);

    penJoinInput = new QComboBox();
    penJoinInput->addItem("MiterJoin", Qt::MiterJoin);
    penJoinInput->addItem("RoundJoin", Qt::RoundJoin);
    penJoinInput->addItem("BevelJoin", Qt::BevelJoin);

    submit = new QPushButton("Add");
    connect(submit, SIGNAL(clicked(bool)), this, SLOT(onSubmitClicked()));

    formLayout->addRow("Pen Color: ", penColorInput);
    formLayout->addRow("Pen Width: ", penWidthInput);
    formLayout->addRow("Pen Style: ", penStyleInput);
    formLayout->addRow("Pen Cap Style: ", penCapInput);
    formLayout->addRow("Pen Join Style: ", penJoinInput);
    formLayout->addRow(" ", submit);

}

void AddShapeDialog::initPolylineControls()
{
    addNewPolyPointInput = new QPushButton("Add point");
    connect(addNewPolyPointInput, SIGNAL(clicked(bool)), this, SLOT(onPolyPointAdd()));
    formLayout->addRow(" ", addNewPolyPointInput);

    penColorInput = new QComboBox();
    penColorInput->addItem("Blue");
    penColorInput->addItem("Red");
    penColorInput->addItem("Cyan");
    penColorInput->addItem("Green");
    penColorInput->addItem("Yellow");
    penColorInput->addItem("Magenta");
    penColorInput->addItem("Black");

    penWidthInput = new QSpinBox();
    penWidthInput->setRange(0,20);

    penStyleInput = new QComboBox();
    penStyleInput->addItem("SolidLine", static_cast<int>(Qt::SolidLine));
    penStyleInput->addItem("DashLine", static_cast<int>(Qt::DashLine));
    penStyleInput->addItem("DashDotLine", static_cast<int>(Qt::DashDotLine));
    penStyleInput->addItem("DashDotDotLine", static_cast<int>(Qt::DashDotDotLine));

    penCapInput = new QComboBox();
    penCapInput->addItem("SquareCap", Qt::SquareCap);
    penCapInput->addItem("FlatCap", Qt::FlatCap);
    penCapInput->addItem("RoundCap", Qt::RoundCap);

    penJoinInput = new QComboBox();
    penJoinInput->addItem("MiterJoin", Qt::MiterJoin);
    penJoinInput->addItem("RoundJoin", Qt::RoundJoin);
    penJoinInput->addItem("BevelJoin", Qt::BevelJoin);

    submit = new QPushButton("Add");
    connect(submit, SIGNAL(clicked(bool)), this, SLOT(onSubmitClicked()));

    formLayout->addRow("Pen Color: ", penColorInput);
    formLayout->addRow("Pen Width: ", penWidthInput);
    formLayout->addRow("Pen Style: ", penStyleInput);
    formLayout->addRow("Pen Cap Style: ", penCapInput);
    formLayout->addRow("Pen Join Style: ", penJoinInput);
    formLayout->addRow(" ", submit);
}

void AddShapeDialog::initPolygonControls()
{
    addNewPolyPointInput = new QPushButton("Add point");
    connect(addNewPolyPointInput, SIGNAL(clicked(bool)), this, SLOT(onPolyPointAdd()));
    formLayout->addRow(" ", addNewPolyPointInput);

    penColorInput = new QComboBox();
    penColorInput->addItem("Blue");
    penColorInput->addItem("Red");
    penColorInput->addItem("Cyan");
    penColorInput->addItem("Green");
    penColorInput->addItem("Yellow");
    penColorInput->addItem("Magenta");
    penColorInput->addItem("Black");

    penWidthInput = new QSpinBox();
    penWidthInput->setRange(0,20);

    penStyleInput = new QComboBox();
    penStyleInput->addItem("SolidLine", static_cast<int>(Qt::SolidLine));
    penStyleInput->addItem("DashLine", static_cast<int>(Qt::DashLine));
    penStyleInput->addItem("DashDotLine", static_cast<int>(Qt::DashDotLine));
    penStyleInput->addItem("DashDotDotLine", static_cast<int>(Qt::DashDotDotLine));

    penCapInput = new QComboBox();
    penCapInput->addItem("SquareCap", Qt::SquareCap);
    penCapInput->addItem("FlatCap", Qt::FlatCap);
    penCapInput->addItem("RoundCap", Qt::RoundCap);

    penJoinInput = new QComboBox();
    penJoinInput->addItem("MiterJoin", Qt::MiterJoin);
    penJoinInput->addItem("RoundJoin", Qt::RoundJoin);
    penJoinInput->addItem("BevelJoin", Qt::BevelJoin);

    brushColorInput = new QComboBox();
    brushColorInput->addItem("Blue");
    brushColorInput->addItem("Red");
    brushColorInput->addItem("Cyan");
    brushColorInput->addItem("Yellow");
    brushColorInput->addItem("Magenta");
    brushColorInput->addItem("Black");

    brushStyleInput = new QComboBox();
    brushStyleInput->addItem("SolidPattern", static_cast<int>(Qt::SolidPattern));
    brushStyleInput->addItem("VerPattern", static_cast<int>(Qt::VerPattern));
    brushStyleInput->addItem("HorPattern", static_cast<int>(Qt::HorPattern));

    submit = new QPushButton("Add");
    connect(submit, SIGNAL(clicked(bool)), this, SLOT(onSubmitClicked()));

    formLayout->addRow("Pen Color: ", penColorInput);
    formLayout->addRow("Pen Width: ", penWidthInput);
    formLayout->addRow("Pen Style: ", penStyleInput);
    formLayout->addRow("Pen Cap Style: ", penCapInput);
    formLayout->addRow("Pen Join Style: ", penJoinInput);
    formLayout->addRow("Brush Color: ", brushColorInput);
    formLayout->addRow("Brush Style: ", brushStyleInput);
    formLayout->addRow(" ", submit);
}

void AddShapeDialog::initRectangleControls()
{
    penColorInput = new QComboBox();
    penColorInput->addItem("Blue");
    penColorInput->addItem("Red");
    penColorInput->addItem("Cyan");
    penColorInput->addItem("Green");
    penColorInput->addItem("Yellow");
    penColorInput->addItem("Magenta");
    penColorInput->addItem("Black");

    penWidthInput = new QSpinBox();
    penWidthInput->setRange(0,20);

    penStyleInput = new QComboBox();
    penStyleInput->addItem("SolidLine", static_cast<int>(Qt::SolidLine));
    penStyleInput->addItem("DashLine", static_cast<int>(Qt::DashLine));
    penStyleInput->addItem("DashDotLine", static_cast<int>(Qt::DashDotLine));
    penStyleInput->addItem("DashDotDotLine", static_cast<int>(Qt::DashDotDotLine));

    penCapInput = new QComboBox();
    penCapInput->addItem("SquareCap", Qt::SquareCap);
    penCapInput->addItem("FlatCap", Qt::FlatCap);
    penCapInput->addItem("RoundCap", Qt::RoundCap);

    penJoinInput = new QComboBox();
    penJoinInput->addItem("MiterJoin", Qt::MiterJoin);
    penJoinInput->addItem("RoundJoin", Qt::RoundJoin);
    penJoinInput->addItem("BevelJoin", Qt::BevelJoin);

    brushColorInput = new QComboBox();
    brushColorInput->addItem("Blue");
    brushColorInput->addItem("Red");
    brushColorInput->addItem("Cyan");
    brushColorInput->addItem("Yellow");
    brushColorInput->addItem("Magenta");
    brushColorInput->addItem("Black");

    brushStyleInput = new QComboBox();
    brushStyleInput->addItem("SolidPattern", static_cast<int>(Qt::SolidPattern));
    brushStyleInput->addItem("VerPattern", static_cast<int>(Qt::VerPattern));
    brushStyleInput->addItem("HorPattern", static_cast<int>(Qt::HorPattern));

    submit = new QPushButton("Add");
    connect(submit, SIGNAL(clicked(bool)), this, SLOT(onSubmitClicked()));

    xPositionInput = new QLineEdit();
    xPositionInput->setValidator(new QIntValidator(this));
    yPositionInput = new QLineEdit();
    yPositionInput->setValidator(new QIntValidator(this));
    widthInput = new QLineEdit();
    widthInput->setValidator(new QIntValidator(this));
    heightInput = new QLineEdit();
    heightInput->setValidator(new QIntValidator(this));


    formLayout->addRow("Top left X: ", xPositionInput);
    formLayout->addRow("Top left Y: ", yPositionInput);
    formLayout->addRow("Width: ", widthInput);
    formLayout->addRow("Height", heightInput);
    formLayout->addRow("Pen Color: ", penColorInput);
    formLayout->addRow("Pen Width: ", penWidthInput);
    formLayout->addRow("Pen Style: ", penStyleInput);
    formLayout->addRow("Pen Cap Style: ", penCapInput);
    formLayout->addRow("Pen Join Style: ", penJoinInput);
    formLayout->addRow("Brush Color: ", brushColorInput);
    formLayout->addRow("Brush Style: ", brushStyleInput);
    formLayout->addRow(" ", submit);

}

void AddShapeDialog::initEllipseControls()
{
    penColorInput = new QComboBox();
    penColorInput->addItem("Blue");
    penColorInput->addItem("Red");
    penColorInput->addItem("Cyan");
    penColorInput->addItem("Green");
    penColorInput->addItem("Yellow");
    penColorInput->addItem("Magenta");
    penColorInput->addItem("Black");

    penWidthInput = new QSpinBox();
    penWidthInput->setRange(0,20);

    penStyleInput = new QComboBox();
    penStyleInput->addItem("SolidLine", static_cast<int>(Qt::SolidLine));
    penStyleInput->addItem("DashLine", static_cast<int>(Qt::DashLine));
    penStyleInput->addItem("DashDotLine", static_cast<int>(Qt::DashDotLine));
    penStyleInput->addItem("DashDotDotLine", static_cast<int>(Qt::DashDotDotLine));

    penCapInput = new QComboBox();
    penCapInput->addItem("SquareCap", Qt::SquareCap);
    penCapInput->addItem("FlatCap", Qt::FlatCap);
    penCapInput->addItem("RoundCap", Qt::RoundCap);

    penJoinInput = new QComboBox();
    penJoinInput->addItem("MiterJoin", Qt::MiterJoin);
    penJoinInput->addItem("RoundJoin", Qt::RoundJoin);
    penJoinInput->addItem("BevelJoin", Qt::BevelJoin);

    brushColorInput = new QComboBox();
    brushColorInput->addItem("Blue");
    brushColorInput->addItem("Red");
    brushColorInput->addItem("Cyan");
    brushColorInput->addItem("Yellow");
    brushColorInput->addItem("Magenta");
    brushColorInput->addItem("Black");

    brushStyleInput = new QComboBox();
    brushStyleInput->addItem("SolidPattern", static_cast<int>(Qt::SolidPattern));
    brushStyleInput->addItem("VerPattern", static_cast<int>(Qt::VerPattern));
    brushStyleInput->addItem("HorPattern", static_cast<int>(Qt::HorPattern));

    submit = new QPushButton("Add");
    connect(submit, SIGNAL(clicked(bool)), this, SLOT(onSubmitClicked()));

    xPositionInput = new QLineEdit();
    xPositionInput->setValidator(new QIntValidator(this));
    yPositionInput = new QLineEdit();
    yPositionInput->setValidator(new QIntValidator(this));
    widthInput = new QLineEdit();
    widthInput->setValidator(new QIntValidator(this));
    heightInput = new QLineEdit();
    heightInput->setValidator(new QIntValidator(this));


    formLayout->addRow("Top left X: ", xPositionInput);
    formLayout->addRow("Top left Y: ", yPositionInput);
    formLayout->addRow("Width: ", widthInput);
    formLayout->addRow("Height", heightInput);
    formLayout->addRow("Pen Color: ", penColorInput);
    formLayout->addRow("Pen Width: ", penWidthInput);
    formLayout->addRow("Pen Style: ", penStyleInput);
    formLayout->addRow("Pen Cap Style: ", penCapInput);
    formLayout->addRow("Pen Join Style: ", penJoinInput);
    formLayout->addRow("Brush Color: ", brushColorInput);
    formLayout->addRow("Brush Style: ", brushStyleInput);
    formLayout->addRow(" ", submit);
}

void AddShapeDialog::initCircleControls()
{
    penColorInput = new QComboBox();
    penColorInput->addItem("Blue");
    penColorInput->addItem("Red");
    penColorInput->addItem("Cyan");
    penColorInput->addItem("Green");
    penColorInput->addItem("Yellow");
    penColorInput->addItem("Magenta");
    penColorInput->addItem("Black");

    penWidthInput = new QSpinBox();
    penWidthInput->setRange(0,20);

    penStyleInput = new QComboBox();
    penStyleInput->addItem("SolidLine", static_cast<int>(Qt::SolidLine));
    penStyleInput->addItem("DashLine", static_cast<int>(Qt::DashLine));
    penStyleInput->addItem("DashDotLine", static_cast<int>(Qt::DashDotLine));
    penStyleInput->addItem("DashDotDotLine", static_cast<int>(Qt::DashDotDotLine));

    penCapInput = new QComboBox();
    penCapInput->addItem("SquareCap", Qt::SquareCap);
    penCapInput->addItem("FlatCap", Qt::FlatCap);
    penCapInput->addItem("RoundCap", Qt::RoundCap);

    penJoinInput = new QComboBox();
    penJoinInput->addItem("MiterJoin", Qt::MiterJoin);
    penJoinInput->addItem("RoundJoin", Qt::RoundJoin);
    penJoinInput->addItem("BevelJoin", Qt::BevelJoin);

    brushColorInput = new QComboBox();
    brushColorInput->addItem("Blue");
    brushColorInput->addItem("Red");
    brushColorInput->addItem("Cyan");
    brushColorInput->addItem("Yellow");
    brushColorInput->addItem("Magenta");
    brushColorInput->addItem("Black");

    brushStyleInput = new QComboBox();
    brushStyleInput->addItem("SolidPattern", static_cast<int>(Qt::SolidPattern));
    brushStyleInput->addItem("VerPattern", static_cast<int>(Qt::VerPattern));
    brushStyleInput->addItem("HorPattern", static_cast<int>(Qt::HorPattern));

    submit = new QPushButton("Add");
    connect(submit, SIGNAL(clicked(bool)), this, SLOT(onSubmitClicked()));

    xPositionInput = new QLineEdit();
    xPositionInput->setValidator(new QIntValidator(this));
    yPositionInput = new QLineEdit();
    yPositionInput->setValidator(new QIntValidator(this));
    widthInput = new QLineEdit();
    widthInput->setValidator(new QIntValidator(this));

    formLayout->addRow("Top left X: ", xPositionInput);
    formLayout->addRow("Top left Y: ", yPositionInput);
    formLayout->addRow("Radius: ", widthInput);
    formLayout->addRow("Pen Color: ", penColorInput);
    formLayout->addRow("Pen Width: ", penWidthInput);
    formLayout->addRow("Pen Style: ", penStyleInput);
    formLayout->addRow("Pen Cap Style: ", penCapInput);
    formLayout->addRow("Pen Join Style: ", penJoinInput);
    formLayout->addRow("Brush Color: ", brushColorInput);
    formLayout->addRow("Brush Style: ", brushStyleInput);
    formLayout->addRow(" ", submit);
}

void AddShapeDialog::initTextControls()
{
    xPositionInput = new QLineEdit();
    xPositionInput->setValidator(new QIntValidator(this));
    yPositionInput = new QLineEdit();
    yPositionInput->setValidator(new QIntValidator(this));
    widthInput = new QLineEdit();
    widthInput->setValidator(new QIntValidator(this));
    heightInput = new QLineEdit();
    heightInput->setValidator(new QIntValidator(this));

    textInput = new QLineEdit();
    textColorInput = new QComboBox();
    textColorInput->addItem("Blue");
    textColorInput->addItem("Red");
    textColorInput->addItem("Cyan");
    textColorInput->addItem("Yellow");
    textColorInput->addItem("Black");
    textColorInput->addItem("Magenta");

    textAlignmentInput = new QComboBox();
    textAlignmentInput->addItem("Left");
    textAlignmentInput->addItem("Center");
    textAlignmentInput->addItem("Right");

    textPointSizeInput = new QSpinBox();
    textPointSizeInput->setRange(0, 24);

    textFontFamilyInput = new QComboBox();
    textFontFamilyInput->addItem("Comic Sans MS");

    textFontStyleInput = new QComboBox();
    textFontStyleInput->addItem("StyleNormal", QFont::StyleNormal);
    textFontStyleInput->addItem("StyleItalic", QFont::StyleItalic);
    textFontStyleInput->addItem("StyleOblique", QFont::StyleOblique);

    textFontWeightInput = new QSpinBox();
    textFontWeightInput->setRange(0, 99);

    submit = new QPushButton("Add");
    connect(submit, SIGNAL(clicked(bool)), this, SLOT(onSubmitClicked()));

    formLayout->addRow("Top left X: ", xPositionInput);
    formLayout->addRow("Top left Y: ", yPositionInput);
    formLayout->addRow("Width: ", widthInput);
    formLayout->addRow("Height", heightInput);
    formLayout->addRow("Text: ", textInput);
    formLayout->addRow("Text Color: ", textColorInput);
    formLayout->addRow("Text Size: ", textPointSizeInput);
    formLayout->addRow("Text Font: ", textFontFamilyInput);
    formLayout->addRow("Text Font Style: ", textFontStyleInput);
    formLayout->addRow("Text Font Weight: ", textFontWeightInput);
    formLayout->addRow(" ", submit);

}

void AddShapeDialog::onSubmitClicked()
{
    if (shapeTypeInput->currentText() == "Line")
    {
        if (lineFirstXPointInput->text() == "" || lineFirstYPointInput->text() == ""
                || lineSecondXPointInput->text() == "" || lineSecondYPointInput->text() == "")
        {
            QMessageBox q;
            q.setText("Incomplete fields!");
            q.exec();
        }
        else
        {
            QPoint p1(lineFirstXPointInput->text().toInt(), lineFirstYPointInput->text().toInt());
            QPoint p2(lineSecondXPointInput->text().toInt(), lineSecondYPointInput->text().toInt());
            dynamic_cast<Line*>(shape)->setPoints(p1, p2);
            shape->setPen(string_to_color(penColorInput->currentText()), penWidthInput->value(),
                          string_to_penstyle(penStyleInput->currentText()),
                          string_to_capstyle(penCapInput->currentText()),
                          string_to_joinstyle(penJoinInput->currentText()));
            this->close();
        }

    }
    else if (shapeTypeInput->currentText() == "Polyline")
    {
        int pointCount = 0;
        for (int i = 3; i < formLayout->rowCount() - 6; i++)
        {
            QPointF point;
            for (int j = 0; j < formLayout->itemAt(j)->layout()->children().size(); j++)
            {
                if (j == 1) //x input
                {

                    point.setX(dynamic_cast<QLineEdit*>(formLayout->itemAt(j)->layout()->children()[j])->text().toFloat());
                }
                else if (j == 3) //y input
                {
                    point.setY(dynamic_cast<QLineEdit*>(formLayout->itemAt(j)->layout()->children()[j])->text().toFloat());
                }
            }
        }
    }
    else if (shapeTypeInput->currentText() == "Polygon")
    {
        int pointCount = 0;
        for (int i = 3; i < formLayout->rowCount() - 6; i++)
        {
            QPointF point;
            for (int j = 0; j < formLayout->itemAt(j)->layout()->children().size(); j++)
            {
                if (j == 1) //x input
                {

                    point.setX(dynamic_cast<QLineEdit*>(formLayout->itemAt(j)->layout()->children()[j])->text().toFloat());
                }
                else if (j == 3) //y input
                {
                    point.setY(dynamic_cast<QLineEdit*>(formLayout->itemAt(j)->layout()->children()[j])->text().toFloat());
                }
            }
        }
    }
    else if (shapeTypeInput->currentText() == "Rectangle")
    {
        QPoint position;
        position.setX(xPositionInput->text().toInt());
        position.setY(yPositionInput->text().toInt());
        dynamic_cast<Rectangle*>(shape)->setPosition(position);
        dynamic_cast<Rectangle*>(shape)->setDimensions(
                    widthInput->text().toInt(), heightInput->text().toInt());
        shape->setPen(string_to_color(penColorInput->currentText()), penWidthInput->value(),
                      string_to_penstyle(penStyleInput->currentText()),
                      string_to_capstyle(penCapInput->currentText()),
                      string_to_joinstyle(penJoinInput->currentText()));
        shape->setBrush(string_to_color(brushColorInput->currentText()),
                        string_to_brushstyle(brushStyleInput->currentText()));
        this->close();

    }
    else if (shapeTypeInput->currentText() == "Ellipse")
    {
        QPointF position;
        position.setX(xPositionInput->text().toFloat());
        position.setY(yPositionInput->text().toFloat());
        dynamic_cast<Ellipse*>(shape)->setPosition(position);
        dynamic_cast<Ellipse*>(shape)->setDimensions(
                    widthInput->text().toFloat(), heightInput->text().toFloat());
        shape->setPen(string_to_color(penColorInput->currentText()), penWidthInput->value(),
                      string_to_penstyle(penStyleInput->currentText()),
                      string_to_capstyle(penCapInput->currentText()),
                      string_to_joinstyle(penJoinInput->currentText()));
        shape->setBrush(string_to_color(brushColorInput->currentText()),
                        string_to_brushstyle(brushStyleInput->currentText()));
        this->close();
    }
    else if (shapeTypeInput->currentText() == "Circle")
    {
        QPointF position;
        position.setX(xPositionInput->text().toFloat());
        position.setY(yPositionInput->text().toFloat());
        dynamic_cast<Circle*>(shape)->setPosition(position);
        dynamic_cast<Circle*>(shape)->setRadius(widthInput->text().toFloat());
        shape->setPen(string_to_color(penColorInput->currentText()), penWidthInput->value(),
                      string_to_penstyle(penStyleInput->currentText()),
                      string_to_capstyle(penCapInput->currentText()),
                      string_to_joinstyle(penJoinInput->currentText()));
        shape->setBrush(string_to_color(brushColorInput->currentText()),
                        string_to_brushstyle(brushStyleInput->currentText()));
        this->close();
    }
    else if (shapeTypeInput->currentText() == "Text")
    {
        QPointF position;
        position.setX(xPositionInput->text().toFloat());
        position.setY(yPositionInput->text().toFloat());
        dynamic_cast<Text*>(shape)->setPosition(position);
        dynamic_cast<Text*>(shape)->setAlignment(textAlignmentInput->currentText());
        dynamic_cast<Text*>(shape)->setTextString(textInput->text());
        shape->setPen(string_to_color(textColorInput->currentText()));
        QFont f;
        f.setFamily("Comic Sans MS");
        f.setWeight(textFontWeightInput->value());
        f.setPointSize(textPointSizeInput->value());
        f.setStyle(string_to_textstyle(textFontStyleInput->currentText()));
        shape->setFont(f);
        this->close();
    }

}

/**
 * @brief Initializes UI controls for adding a shape.
 */
void AddShapeDialog::onShapeTypeSelected()
{
    int shapeType = shapeTypeInput->currentIndex();
    switch (shapeType)
    {
        case 0: //Line
        {
            delete shape;
            shape = new Line(this, 0);
            for (int i = formLayout->rowCount(); i > 1; i--)
            {
                formLayout->removeRow(i);
            }
            initLineControls();
        }
        case 1: //Polyline
        {
            delete shape;
            shape = new Polyline(this, 0);
            for (int i = formLayout->rowCount(); i > 1; i--)
            {
                formLayout->removeRow(i);
            }
            initPolylineControls();
            break;
        }
        case 2: //Polygon
        {
            delete shape;
            shape = new Polygon(this, 0);
            for (int i = formLayout->rowCount(); i > 1; i--)
            {
                formLayout->removeRow(i);
            }
            initPolygonControls();
            break;
        }
        case 3: //Rectangle
        {
            delete shape;
            shape = new Rectangle(this, 0);
            for (int i = formLayout->rowCount(); i > 1; i--)
            {
                formLayout->removeRow(i);
            }
            initRectangleControls();
            break;
        }
        case 4: //Ellipse
        {
            delete shape;
            shape = new Ellipse(this, 0);
            for (int i = formLayout->rowCount(); i > 1; i--)
            {
                formLayout->removeRow(i);
            }
            initEllipseControls();
            break;
        }
        case 5: //Circle
        {
            delete shape;
            shape = new Circle(this, 0);
            for (int i = formLayout->rowCount(); i > 1; i--)
            {
                formLayout->removeRow(i);
            }
            initCircleControls();
            break;
        }
        case 6: //Text
        {
            delete shape;
            shape = new Text(this, 0);
            for (int i = formLayout->rowCount(); i > 1; i--)
            {
                formLayout->removeRow(i);
            }
            initTextControls();
            break;
        }
    }
}

void AddShapeDialog::onPolyPointAdd()
{
    QWidget* row = new QWidget();
    QHBoxLayout* rowLayout = new QHBoxLayout();
    rowLayout->addWidget(new QLabel("X: "));
    QLineEdit* x = new QLineEdit();
    x->setValidator(new QIntValidator(this));
    rowLayout->addWidget(x);
    rowLayout->addWidget(new QLabel("Y: "));
    QLineEdit* y = new QLineEdit();
    y->setValidator(new QIntValidator(this));
    rowLayout->addWidget(y);
    row->setLayout(rowLayout);
    formLayout->insertRow(2, " ", row);
}


void AddShapeDialog::reject()
{
    exited = true;
    QDialog::reject();
}
