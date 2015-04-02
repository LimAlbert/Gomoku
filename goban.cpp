#include "goban.h"
#include <iostream>

Goban::Goban()
{
    this->_Scene = new QGraphicsScene;
    QGraphicsItem *goban_item;
    QPixmap goban;
    goban.load(GOBAN_PATH, 0, Qt::AutoColor);
    goban = goban.scaledToHeight(570);
    goban = goban.scaledToWidth(570);
    goban_item = this->_Scene->addPixmap(goban);
    this->_Vue = new MyQGraphicsView(this->_Scene);
}

MyQGraphicsView   *Goban::GetVue() const
{
    return (this->_Vue);
}

QGraphicsScene   *Goban::GetScene() const
{
    return (this->_Scene);
}


