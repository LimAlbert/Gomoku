#ifndef PIECE_H
#define PIECE_H

#include <QtWidgets/QMainWindow>
#include <QtGui>
#include <QMouseEvent>
#include <QPixmap>
#include <QtWidgets/QGraphicsItem>
#include <stdint.h>
#include "myqgraphicsview.h"
#include "define.h"

class Piece
{
private:
   QGraphicsItem    *_Item;
   QPixmap          _Image;
   uint32_t         _Team;
   int              _X;
   int              _Y;
   std::string      _Str;

public:
    Piece(int const team, int const x, int const y, QGraphicsScene *&Scene);
    Piece(int const team, int const x, int const y);
    Piece(int const team, std::string const &string);
    int             getX() const;
    int             getY() const;
    uint32_t        getTeam() const;
    std::string     getString() const;
    QGraphicsItem   *getItem() const;

};

#endif // PIECE_H
