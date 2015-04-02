#include "piece.h"

Piece::Piece(int const team, int const x, int const y, QGraphicsScene *&Scene)
    : _Team(team), _X(x), _Y(y)
{
    if (this->_Team == NOIR)
        this->_Image.load(NOIR_PATH, 0, Qt::AutoColor);
    else
        this->_Image.load(BLANC_PATH, 0, Qt::AutoColor);
    this->_Image = this->_Image.scaledToHeight(30);
    this->_Image = this->_Image.scaledToWidth(30);
    this->_Item = Scene->addPixmap(this->_Image);
    this->_Item->setPos(this->_X, this->_Y);
}

Piece::Piece(int const team, int const x, int const y)
    : _Team(team), _X(x), _Y(y)
{
}

Piece::Piece(int const team, std::string const &string)
    : _Team(team), _Str(string)
{
}
int             Piece::getX() const
{
    return (this->_X);
}

int             Piece::getY() const
{
    return (this->_Y);
}

uint32_t        Piece::getTeam() const
{
    return (this->_Team);
}

std::string     Piece::getString() const
{
    return (this->_Str);
}

QGraphicsItem   *Piece::getItem() const
{
    return (this->_Item);
}
