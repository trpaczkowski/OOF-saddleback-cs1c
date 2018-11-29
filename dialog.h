#ifndef DIALOG_H
#define DIALOG_H


#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QtWidgets>
#include <QFormLayout>
#include "Shape.h"
#include "text.h"

/**
 * @brief A dialog window to remove a particular shape by ID.
 */
class RemoveShapeDialog : public QDialog
{
    Q_OBJECT

public:
    RemoveShapeDialog(QWidget* parent = 0);
    int getRemoveId() {return removeId;}
    void reject() override;
    bool exited;

private slots:
    void setRemoveId();

private:
    int removeId;
    QLineEdit* input;
    QPushButton* submit;
};

/**
 * @brief A dialog window to add a new shape to the render window.
 */
class AddShapeDialog : public QDialog
{
    Q_OBJECT

public:
    AddShapeDialog(QWidget* parent = 0);
    Shape* getShape() {return shape;}
    void reject() override;
    bool exited;
    void initLineControls();
    void initPolylineControls();
    void initPolygonControls();
    void initRectangleControls();
    void initEllipseControls();
    void initCircleControls();
    void initTextControls();

private:
    Shape* shape;
    QFormLayout* formLayout;
    QPushButton* submit;
    //dimension inputs
    QLineEdit* widthInput;
    QLineEdit* heightInput;
    QLineEdit* xPositionInput;
    QLineEdit* yPositionInput;
    QLineEdit* lineFirstXPointInput;
    QLineEdit* lineFirstYPointInput;
    QLineEdit* lineSecondXPointInput;
    QLineEdit* lineSecondYPointInput;

    /*
     * To allow variable number of points inputted for polygon
     * or polyline, we allow the admin to press a button to create
     * another input field for each point.
     */
    QPushButton* addNewPolyPointInput;

    //other shape inputs
    QLineEdit* textInput;
    QComboBox* shapeTypeInput;
    QSpinBox* penWidthInput;
    QComboBox* penStyleInput;
    QComboBox* penJoinInput;
    QComboBox* penCapInput;
    QComboBox* penColorInput;
    QComboBox* brushColorInput;
    QComboBox* brushStyleInput;
    QComboBox* textAlignmentInput;
    QComboBox* textColorInput;
    QComboBox* textFontStyleInput;
    QComboBox* textFontFamilyInput;
    QSpinBox* textPointSizeInput;
    QSpinBox* textFontWeightInput;
private slots:
    void onShapeTypeSelected();
    void onPolyPointAdd();
    void onSubmitClicked();
};

/**
 * @brief A dialog to specify new coordinates for a shape.
 */
class MoveShapeDialog : public QDialog
{
    Q_OBJECT
public:
    MoveShapeDialog(QWidget* parent = 0);
    int getMoveId() {return moveId;}
    int getXMoveCoord() {return x_move;}
    int getYMoveCoord() {return y_move;}
    void reject() override;
    bool exited;
private:
    int moveId;
    int x_move;
    int y_move;
    QPushButton* submit;
    QLineEdit* idInput;
    QLineEdit* xInput;
    QLineEdit* yInput;
private slots:
    void setMoveInfo();
};

#endif // DIALOG_H
