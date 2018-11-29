#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QWidget>
#include "Shape.h"

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    RenderArea(QWidget *parent = 0);
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;
    void setXMove(int x) {x_move_coord = x;}
    void setYMove(int y) {y_move_coord = y;}
    void setMoveId(int id) {move_id = id;}
    void setRemoveId(int id) {remove_id = id;}
    void addShape(Shape* s) {shapes.push_back(s);}
    vector<Shape*>* getShapes() {return &shapes;}
    int getShapeIndexById(int id);
    Shape * get_shape(QTextStream& shape_text_stream);
    void populate_shapes(QString& filename, vector<Shape*> & shapes);
    int getNewId();
    ~RenderArea();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    int x_move_coord; //coords of the shape to move
    int y_move_coord;
    int move_id; //id of the shape to move
    int remove_id; //id of the shape to delete

    vector<Shape*> shapes;

};

Qt::GlobalColor string_to_color(QString);
Qt::PenStyle string_to_penstyle(QString);
Qt::PenCapStyle string_to_capstyle(QString);
Qt::PenJoinStyle string_to_joinstyle(QString);
Qt::BrushStyle string_to_brushstyle(QString);
QFont::Style string_to_textstyle(QString);

#endif // RENDERAREA_H
