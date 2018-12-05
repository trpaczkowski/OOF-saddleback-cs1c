#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Should set to false again
    ui->Tab_Move->setEnabled(true);
    ui->Tab_Shape->setEnabled(true);
    ui->tab_setProperties->setEnabled(true);
    //ui->tab_delete->setEnabled(true);

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

    ui->Tab_Move->setEnabled(adminPrivW);
    ui->Tab_Shape->setEnabled(adminPrivW);
    ui->tab_setProperties->setEnabled(adminPrivW);
    //ui->tab_delete->setEnabled(adminPrivW);

    if( ui->Tab_Move->isEnabled())
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

    QMessageBox::information(this, "Adding Shape", "Shape Added!");
    qDebug ("Mainwindow about to add");
    switch(shapeInput)
    {

        case 0:
        {
            //Line
            qDebug ("Mainwindow about to add line");
            Line *addLine = new Line(this, 0);

            addLine->setShape(ShapeType::LineType);
            addLine->setId(ui->widget->getSizing());
            addLine->setPen(getPenColor(), getPenWidth(), getPenStyle(), getPenCapStyle(), getPenJoinStyle());
            addLine->setBrush(getBrushColor(), getBrushStyle());
            //Set Point
            QPoint firstCoordinate(ui->spinBox_line_firstX->value(), ui->spinBox_line_firstY->value());
            QPoint secondCoordinate(ui->spinBox_line_secondX->value(), ui->spinBox_line_secondY->value());
            addLine->setPoints(firstCoordinate, secondCoordinate);

            //canvasUi.shapeAdd(addLine);
            qDebug ("Mainwindow about to add line pt 2");
            ui->widget->shapeAdd(addLine);
            qDebug ("Mainwindow finished adding line");

            break;
         }

        //Polyline
        case 1:
        {
            qDebug ("Mainwindow about to add polyline");
            Polyline *addPolyLine = new Polyline(this, 0);

            addPolyLine->setShape(ShapeType::PolylineType);
            addPolyLine->setId(ui->widget->getSizing());
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
            addPolyLine->addNumPoints(ui->spinBox_polyline_pointsAdded->value());

            //Check if more points added
            if(ui->spinBox_polyline_pointsAdded->value() >= 3)
            {
                addPolyLine->addPoint(coordinate3);
                if(ui->spinBox_polyline_pointsAdded->value() >= 4)
                {
                    addPolyLine->addPoint(coordinate4);
                    if(ui->spinBox_polyline_pointsAdded->value() >= 5)
                    {
                        addPolyLine->addPoint(coordinate5);
                        if(ui->spinBox_polyline_pointsAdded->value() == 6)
                        {
                            addPolyLine->addPoint(coordinate6);
                        }
                    }
                }
            }

            //canvasUi.shapeAdd(addPolyLine);

            qDebug ("Mainwindow about to add polyline pt 2");
            ui->widget->shapeAdd(addPolyLine);
                    qDebug ("Mainwindow finished adding polyline");
            break;
        }

        //Polygon
        case 2:
        {
        qDebug ("Mainwindow about to add polygon");
            Polygon *addPolygon = new Polygon(this, 0);

            addPolygon->setShape(ShapeType::PolygonType);
            addPolygon->setId(ui->widget->getSizing());
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
            addPolygon->addNumPoints(ui->spinBox_polygon_pointsAdded->value());


            //Check if more points added
            if(ui->spinBox_polygon_pointsAdded->value() >= 4)
            {
                addPolygon->addPoint(coordinate4);
                if(ui->spinBox_polygon_pointsAdded->value() >= 5)
                {
                    addPolygon->addPoint(coordinate5);
                    if(ui->spinBox_polygon_pointsAdded->value() >= 6)
                    {
                        addPolygon->addPoint(coordinate6);
                        if(ui->spinBox_polygon_pointsAdded->value() >= 7)
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

            //canvasUi.shapeAdd(addPolygon);
qDebug ("Mainwindow about to add polygon pt2");
            ui->widget->shapeAdd(addPolygon);
            qDebug ("Mainwindow polygon added");
            break;
        }

        //Rectangle
        case 3:
        {
        qDebug ("Mainwindow about to add rect");
            Rectangle *addRect = new Rectangle(this, 0);

            addRect->setShape(ShapeType::RectangleType);
            addRect->setId(ui->widget->getSizing());
            addRect->setPen(getPenColor(), getPenWidth(), getPenStyle(), getPenCapStyle(), getPenJoinStyle());
            addRect->setBrush(getBrushColor(), getBrushStyle());

            //Add points
            QPoint center(ui->doubleSpinBox_rect_firstX->value(), ui->doubleSpinBox_rect_firstY->value());

            addRect->setDimensions(ui->doubleSpinBox_rect_width->value(), ui->doubleSpinBox_rect_length->value());
            addRect->setPosition(center);

            //canvasUi.shapeAdd(addRect);

            qDebug ("Mainwindow about to add rect pt2");
            ui->widget->shapeAdd(addRect);
            qDebug ("Mainwindow rect added");

            break;
        }

        //Ellipse
        case 4:
        {
        qDebug ("Mainwindow about to add ellip");
            Ellipse *addEllipse = new Ellipse(this, 0);

            addEllipse->setShape(ShapeType::EllipseType);
            addEllipse->setId(ui->widget->getSizing());
            addEllipse->setPen(getPenColor(), getPenWidth(), getPenStyle(), getPenCapStyle(), getPenJoinStyle());
            addEllipse->setBrush(getBrushColor(), getBrushStyle());

            //Add points
            QPointF center(ui->doubleSpinBox_ellipse_firstX->value(), ui->doubleSpinBox_ellipse_firstY->value());
            addEllipse->setPosition(center);
            addEllipse->setDimensions(ui->doubleSpinBox_ellipse_axisX->value(), ui->doubleSpinBox_ellipse_axisY->value());

            //canvasUi.shapeAdd(addEllipse);
qDebug ("Mainwindow about to add ellip pt 2");
            ui->widget->shapeAdd(addEllipse);
            qDebug ("Mainwindow ellipse added");
            break;
        }

        //Text
        case 5:
        {
        qDebug ("Mainwindow about to add text");
            Text *addText = new Text(this,0);

            addText->setShape(ShapeType::TextType);
            addText->setId(ui->widget->getSizing() );

            addText->setAlignment(getAlign());
            addText->setText(ui->textEdit->toPlainText());
            addText->setFont(ui->checkBox_bold->isChecked(), ui->checkBox_italic->isChecked(),
                             ui->spinBox_text_point_size->value(),ui->spinBox_text_weight->value());

            //add points
            QPoint center(ui->spinBox_text_X->value(), ui->spinBox_text_Y->value());
            addText->setPosition(center);
            addText->setDimensions(ui->spinBox_text_box_width->value(), ui->spinBox_text_box_hight->value());

            //canvasUi.shapeAdd(addText);
qDebug ("Mainwindow about to add text pts");
            ui->widget->shapeAdd(addText);
            qDebug ("Mainwindow text added");
            break;
        }

    }//End Switch


}

void MainWindow::on_pushButton_deleteShape_clicked()
{
    QMessageBox::information(this, "Deleting Shape", "Shape Deleted!");
    //canvasUi.shapeRemove(ui->spinBox_delete_id->value());
    qDebug ("Mainwindow about to delete");
    ui->widget->shapeRemove(ui->spinBox_delete_id->value());
    qDebug ("Mainwindow finished delete");
}

void MainWindow::on_pushButton_move_clicked()
{
    QMessageBox::information(this, "Moving Shape", "Shape Moved!");
    ui->widget->shapeMove(ui->spinBox_move_id->value(), ui->spinBox_moveX->value(), ui->spinBox_moveY->value());
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

Qt::AlignmentFlag MainWindow::getAlign()
{
    switch(ui->comboBox_text_alignment->currentIndex())
    {
    case 0: {return Qt::AlignLeft;
        break;}
    case 1: {return Qt::AlignCenter;
        break;}
    case 2: {return Qt::AlignRight;
        break;}
    default: {return Qt::AlignLeft;}
    }
}

Qt::GlobalColor MainWindow::getTextColor()
{
    switch(ui->comboBox_textColor->currentIndex())
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


