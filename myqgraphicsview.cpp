#include "myqgraphicsview.h"

MyQGraphicsView::MyQGraphicsView(QGraphicsScene *scene, QWidget * parent)
    : QGraphicsView(scene, parent)
{
}

void    MyQGraphicsView::mousePressEvent(QMouseEvent * event)
{
    emit(clicked(event));
    event->accept();
}
