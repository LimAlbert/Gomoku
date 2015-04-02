#ifndef GOBAN_H
#define GOBAN_H

#include <QtWidgets/QMainWindow>
#include <QtGui>
#include <QMouseEvent>
#include <QtWidgets/QLabel>
#include "myqgraphicsview.h"
#include "piece.h"
#include "define.h"

class Goban : public QLabel
{
private:
    MyQGraphicsView *_Vue;

public:
    Goban();
    QGraphicsScene  *_Scene;
    MyQGraphicsView *GetVue() const;
    QGraphicsScene  *GetScene() const;

};

#endif // GOBAN_H
