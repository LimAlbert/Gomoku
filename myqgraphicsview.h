#ifndef MYQGRAPHICSVIEW_H
#define MYQGRAPHICSVIEW_H

#include <QtWidgets/QMainWindow>
#include <QtGui>
#include <QtWidgets/QGraphicsView>
#include <QMouseEvent>

class MyQGraphicsView : public QGraphicsView
{
    Q_OBJECT;

public:
    MyQGraphicsView(QGraphicsScene * scene, QWidget * parent = 0);
public slots:
    void    mousePressEvent(QMouseEvent * event);

signals:
    void    clicked(QMouseEvent *);
};

#endif // MYQGRAPHICSVIEW_H
