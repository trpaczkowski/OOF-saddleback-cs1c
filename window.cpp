
#include "renderarea.h"
#include "window.h"
#include "Shape.h"
#include "text.h"
#include <iostream>
#include <QtWidgets>
#include "dialog.h"

bool Window::isAdmin = false;

Window::Window()
{
    QString file_names;
    file_names = QFileDialog::getOpenFileName(this, "Select All Data Files", "", "All Files (*)");

    mainLayout = new QVBoxLayout();

    tabs = new QTabWidget();
    miscTab = new QWidget();
    reportsTab = new QWidget();
    renderTab = new QWidget();
    tabs->addTab(reportsTab, "Reports");
    tabs->addTab(renderTab, "Render Screen");
    tabs->addTab(miscTab, "More");
    tabs->setCurrentIndex(1);

    //build render tab
    renderLayout = new QGridLayout(renderTab);
    renderLayout->setColumnStretch(0, 1);
    renderLayout->setColumnStretch(3, 1);
    renderArea = new RenderArea();
    renderLayout->addWidget(renderArea, 0,0,4,4);

    //build the reports tab
    reportLayout = new QGridLayout(reportsTab);
    reportDisplay = new QTextEdit();
    reportDisplay->setReadOnly(true);
    shapeIdReport = new QPushButton("Shapes by ID");
    shapeAreas = new QPushButton("Shapes by Area");
    shapePerimeters = new QPushButton("Shapes by Perimeter");
    reportLayout->addWidget(reportDisplay, 0, 4, 4, 2);
    reportLayout->addWidget(shapeIdReport, 0, 0, 1, 1);
    reportLayout->addWidget(shapeAreas, 1, 0, 1, 1);
    reportLayout->addWidget(shapePerimeters, 2,0,1,1);

    //build the "more" tab
    miscLayout = new QHBoxLayout(miscTab);
    contactInfo = new QLabel("Contact Info\n721 Fifth Avenue\nNew York City, NY 10022\nUnited States\n212-715-7290\n2DGraphicsGuys@gmail.com");
    miscLayout->addWidget(contactInfo);



    //insert admin controls if needed
    if (isAdmin)
    {
        QHBoxLayout* controlPanel = new QHBoxLayout();

        QPushButton* addShape = new QPushButton("Add");
        QPushButton* moveShape = new QPushButton("Move");
        QPushButton* removeShape = new QPushButton("Remove");

        connect(moveShape, SIGNAL(clicked(bool)), this, SLOT(moveShape()));
        connect(removeShape, SIGNAL(clicked(bool)), this, SLOT(removeShape()));
        connect(addShape, SIGNAL(clicked(bool)), this, SLOT(addShape()));

        controlPanel->addWidget(addShape);
        controlPanel->addWidget(moveShape);
        controlPanel->addWidget(removeShape);

        renderLayout->addLayout(controlPanel, 3,2,1,1, Qt::AlignBottom);
    }
    mainLayout->addWidget(tabs);
    setLayout(mainLayout);

    setWindowTitle(tr("Basic Drawing"));
    setMinimumSize(1000, 500);
}

void Window::moveShape() //test this
{
    MoveShapeDialog d;
    d.exec();
    if (!d.exited)
    {
        renderArea->setMoveId(d.getMoveId());
        renderArea->setXMove(d.getXMoveCoord());
        renderArea->setYMove(d.getYMoveCoord());
        update();
    }

}
void Window::removeShape() //test this
{
    RemoveShapeDialog d;
    d.exec();
    if (!d.exited)
    {
        renderArea->setRemoveId(d.getRemoveId());
        update();
    }

}
void Window::addShape()
{
    AddShapeDialog d;
    d.exec();

    update();
}
