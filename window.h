#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "Shape.h"
#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QLabel;
class QSpinBox;
class QMainWindow;
QT_END_NAMESPACE
class RenderArea;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    static bool isAdmin;


private slots:
    void moveShape();
    void addShape();
    void removeShape();

private:
    RenderArea*   renderArea;
    QVBoxLayout*  mainLayout;
    QTabWidget*   tabs;
    QWidget*      miscTab;
    QWidget*      reportsTab;
    QWidget*      renderTab;
    QGridLayout*  renderLayout;
    QGridLayout*  reportLayout;
    QTextEdit*    reportDisplay;
    QPushButton*  shapeIdReport;
    QPushButton*  shapeAreas;
    QPushButton*  shapePerimeters;
    QHBoxLayout*  miscLayout;
    QLabel*       contactInfo;

};

#endif // WINDOW_H
