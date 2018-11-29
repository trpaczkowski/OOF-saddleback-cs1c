#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Tab_Modify->setEnabled(false);
    ui->Tab_Shape->setEnabled(true);
    ui->tab_setProperties->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLogin_triggered()
{
    uiLogin = new AdminLogin(this);
    uiLogin->show();
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

//Will set admin privledges
void MainWindow::SetAdminPriv(bool adminIn)
{
    adminPrivW = adminIn;
}

void MainWindow::on_actionEnable_Disable_Privledges_triggered()
{
    //Gets new admin privledges
    SetAdminPriv(uiLogin->GetAdminPriv());

    ui->Tab_Modify->setEnabled(adminPrivW);
    ui->Tab_Shape->setEnabled(adminPrivW);
    ui->tab_setProperties->setEnabled(adminPrivW);

    if( ui->Tab_Modify->isEnabled())
    {
        QMessageBox::information(this, "Admin Actions", "Admin actions enabled. Check the \"Modify Tab\" for actions.");
        ui->label_userType->setText("Admin user");
    }
    else
    {
        QMessageBox::critical(this, "Admin Actions", "Not allowed to enable! Must login to admin.");
    }


}

//Adding shape
void MainWindow::on_pushButton_clicked()
{
    int shapeInput = ui->tabWidget_addShape->currentIndex();
QMessageBox::critical(this, "Admin Actions", QString::number(ui->tabWidget_addShape->currentIndex()));
    switch(shapeInput)
    {

        case 0:
        {
QMessageBox::critical(this, "Admin Actions", QString::number(canvasUi->rando()) + "hi");
            //Line
            Line *addLine = new Line(this, 0);
QMessageBox::critical(this, "Admin Actions", QString::number(ui->tabWidget_addShape->currentIndex()) + "hi2");
addLine->setId( 0 + 1); //canvasUi->shapeList.size()
            addLine->setPen(getPenColor(), getPenWidth(), getPenStyle(), getPenCapStyle(), getPenJoinStyle());
            addLine->setBrush(getBrushColor(), getBrushStyle());
QMessageBox::critical(this, "Admin Actions", QString::number(ui->tabWidget_addShape->currentIndex()) + "hi3");
            //Set Point
            QPoint firstCoordinate(ui->spinBox_line_firstX->value(), ui->spinBox_line_firstY->value());
            QPoint secondCoordinate(ui->spinBox_line_secondX->value(), ui->spinBox_line_secondY->value());
            addLine->setPoints(firstCoordinate, secondCoordinate);
QMessageBox::critical(this, "Admin Actions", QString::number(ui->tabWidget_addShape->currentIndex()) + "hi4");
//ISSUE            canvasUi->shapeList.push_back(addLine);
QMessageBox::critical(this, "Admin Actions", QString::number(ui->tabWidget_addShape->currentIndex()) + "hi5");
            break;
         }

        //Polyline
        case 1:
        {
            Polyline *addPolyLine = new Polyline();
            addPolyLine->setId(canvasUi->shapeList.size() + 1);
            addPolyLine->setPen(getPenColor(), getPenWidth(), getPenStyle(), getPenCapStyle(), getPenJoinStyle());
            addPolyLine->setBrush(getBrushColor(), getBrushStyle());

            //Add Points
            QPointF coordinate1(ui->doubleSpinBox_polyline_firstX->value(), ui->doubleSpinBox_polyline_firstY->value());
            QPointF coordinate2(ui->doubleSpinBox_polyline_secondX->value(), ui->doubleSpinBox_polyline_secondY->value());
            QPointF coordinate3(ui->doubleSpinBox_polyline_thirdX->value(), ui->doubleSpinBox_polyline_thirdY->value());
            QPointF coordinate4(ui->doubleSpinBox_polyline_fourthX->value(), ui->doubleSpinBox_polyline_fourthY->value());
            QPointF coordinate5(ui->doubleSpinBox_polyline_fifthX->value(), ui->doubleSpinBox_polyline_fifthY->value());
            QPointF coordinate6(ui->doubleSpinBox_polyline_sixthX->value(), ui->doubleSpinBox_polyline_sixthY->value());

            addPolyLine->addPoint(coordinate1);
            addPolyLine->addPoint(coordinate2);

            //Check if more points added
            if(ui->spinBox_polyline_pointsAdded->value() == 3)
            {
                addPolyLine->addPoint(coordinate3);
                if(ui->spinBox_polyline_pointsAdded->value() == 4)
                {
                    addPolyLine->addPoint(coordinate4);
                    if(ui->spinBox_polyline_pointsAdded->value() == 5)
                    {
                        addPolyLine->addPoint(coordinate5);
                        if(ui->spinBox_polyline_pointsAdded->value() == 6)
                        {
                            addPolyLine->addPoint(coordinate6);
                        }
                    }
                }
            }

            canvasUi->shapeList.push_back(addPolyLine);
            break;
        }

        //Polygon
        case 2:
        {
            Polygon *addPolygon = new Polygon();
            addPolygon->setId(canvasUi->shapeList.size() + 1);
            addPolygon->setPen(getPenColor(), getPenWidth(), getPenStyle(), getPenCapStyle(), getPenJoinStyle());
            addPolygon->setBrush(getBrushColor(), getBrushStyle());

            //Add points
            QPointF coordinate1(ui->doubleSpinBox_polygon_firstX->value(), ui->doubleSpinBox_polygon_firstY->value());
            QPointF coordinate2(ui->doubleSpinBox_polygon_secondX->value(), ui->doubleSpinBox_polygon_secondY->value());
            QPointF coordinate3(ui->doubleSpinBox_polygon_thirdX->value(), ui->doubleSpinBox_polygon_thirdY->value());
            QPointF coordinate4(ui->doubleSpinBox_polygon_fourthX->value(), ui->doubleSpinBox_polygon_fourthY->value());
            QPointF coordinate5(ui->doubleSpinBox_polygon_fifthX->value(), ui->doubleSpinBox_polygon_fifthY->value());
            QPointF coordinate6(ui->doubleSpinBox_polygon_sixthX->value(), ui->doubleSpinBox_polygon_sixthY->value());
            QPointF coordinate7(ui->doubleSpinBox_polygon_seventhX->value(), ui->doubleSpinBox_polygon_seventhY->value());
            QPointF coordinate8(ui->doubleSpinBox_polygon_eighthX->value(), ui->doubleSpinBox_polygon_eighthY->value());

            addPolygon->addPoint(coordinate1);
            addPolygon->addPoint(coordinate2);
            addPolygon->addPoint(coordinate3);

            //Check if more points added
            if(ui->spinBox_polygon_pointsAdded->value() == 4)
            {
                addPolygon->addPoint(coordinate4);
                if(ui->spinBox_polygon_pointsAdded->value() == 5)
                {
                    addPolygon->addPoint(coordinate5);
                    if(ui->spinBox_polygon_pointsAdded->value() == 6)
                    {
                        addPolygon->addPoint(coordinate6);
                        if(ui->spinBox_polygon_pointsAdded->value() == 7)
                        {
                            addPolygon->addPoint(coordinate7);
                            if(ui->spinBox_polygon_pointsAdded->value() == 8)
                            {
                                addPolygon->addPoint(coordinate8);
                            }
                        }
                    }
                }
            }


            canvasUi->shapeList.push_back(addPolygon);
            break;
        }

        //Rectangle
        case 3:
        {
            Rectangle *addRect = new Rectangle();
            addRect->setId(canvasUi->shapeList.size() + 1);
            addRect->setPen(getPenColor(), getPenWidth(), getPenStyle(), getPenCapStyle(), getPenJoinStyle());
            addRect->setBrush(getBrushColor(), getBrushStyle());

            //Add points
            QPoint center(ui->doubleSpinBox_rect_firstX->value(), ui->doubleSpinBox_rect_firstY->value());

            addRect->setDimensions(ui->doubleSpinBox_rect_width->value(), ui->doubleSpinBox_rect_length->value());
            addRect->setPosition(center);

            canvasUi->shapeList.push_back(addRect);
            break;
        }

        //Ellipse
        case 4:
        {
            Ellipse *addEllipse = new Ellipse();
            addEllipse->setId(canvasUi->shapeList.size() + 1);
            addEllipse->setPen(getPenColor(), getPenWidth(), getPenStyle(), getPenCapStyle(), getPenJoinStyle());
            addEllipse->setBrush(getBrushColor(), getBrushStyle());

            //Add points
            QPointF center(ui->doubleSpinBox_ellipse_firstX->value(), ui->doubleSpinBox_ellipse_firstY->value());
            addEllipse->setPosition(center);
            addEllipse->setDimensions(ui->doubleSpinBox_ellipse_axisX->value(), ui->doubleSpinBox_ellipse_axisY->value());

            canvasUi->shapeList.push_back(addEllipse);
            break;
        }

//        //Text WILL DO LATER
//        case 5:
//        {

//            break;
//        }

    }//End Switch

}

//Pen properties
Qt::GlobalColor MainWindow::getPenColor()
{
    switch(ui->comboBox_setPenColor->currentIndex())
    {
        case 0:
            {return Qt::blue;
            break;}
        case 1:
            {return Qt::red;
            break;}
        case 2:
            {return Qt::green;
            break;}
        case 3:
            {return Qt::yellow;
            break;}
        case 4:
            {return Qt::black;
            break;}
        case 5:
            {return Qt::white;
            break;}
        default:
            {return Qt:: blue;}
    }
}

int MainWindow::getPenWidth()
{
    switch(ui->comboBox_setPenWidth->currentIndex())
    {
    case 0: {return 1;
        break;}
    case 1: {return 5;
        break;}
    case 2: {return 10;
        break;}
    default: {return 1;}
    }
}

Qt::PenStyle MainWindow::getPenStyle()
{
    switch(ui->comboBox_setPenStyle->currentIndex())
    {
    case 0: {return Qt::SolidLine;
        break;}
    case 1: {return Qt::DashLine;
        break;}
    case 2: {return Qt::DotLine;
        break;}
    case 3: {return Qt::DashDotLine;
        break;}
    case 4: {return Qt::DashDotDotLine;
        break;}
    default: {return Qt::SolidLine;}
    }
}

Qt::PenCapStyle MainWindow::getPenCapStyle()
{
    switch (ui->comboBox_setPenCapStyle->currentIndex())
    {
    case 0: {return Qt::SquareCap;
        break;}
    case 1: {return Qt::FlatCap;
        break;}
    case 2: {return Qt::RoundCap;
        break;}
    default: {return Qt::SquareCap;}
    }
}

Qt::PenJoinStyle MainWindow::getPenJoinStyle()
{
    switch(ui->comboBox_setPenJoinStyle->currentIndex())
    {
    case 0: {return Qt::BevelJoin;
        break;}
    case 1: {return Qt::MiterJoin;
        break;}
    case 2: {return Qt::RoundJoin;
        break;}
    default: {return Qt::BevelJoin;}
    }
}

Qt::GlobalColor MainWindow::getBrushColor()
{
    switch(ui->comboBox_setBrushColor->currentIndex())
    {
    case 0: {return Qt::blue;
        break;}
    case 1: {return Qt::red;
        break;}
    case 2: {return Qt::green;
        break;}
    case 3: {return Qt::yellow;
        break;}
    case 4: {return Qt::black;
        break;}
    case 5: {return Qt::white;
        break;}
    default: {return Qt:: blue;}
    }
}

Qt::BrushStyle MainWindow::getBrushStyle()
{
    switch (ui->comboBox_setBrushStyle->currentIndex())
    {
    case 0: {return Qt::NoBrush;
        break;}
    case 1: {return Qt::SolidPattern;
        break;}
    default: {return Qt::NoBrush;}
    }
}

void MainWindow::on_actionhi_triggered()
{

}
