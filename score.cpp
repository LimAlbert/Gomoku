#include "score.h"
#include <iostream>
Score::Score(QWidget *parent)
{
    this->_ScoreLayout = new QHBoxLayout;
    this->_White = new MyLCD(0, 50, 35, parent);
    this->_Black = new MyLCD(0, 50, 35, parent);
    this->_WhiteIcon = new Image(BLANC_PATH);
    this->_WhiteIcon->getImage()->setFixedSize(23, 23);
    this->_BlackIcon = new Image(NOIR_PATH);
    this->_BlackIcon->getImage()->setFixedSize(23, 23);
    this->_ScoreLayout->addWidget(this->_WhiteIcon->getImage());
    this->_ScoreLayout->addWidget(this->_White->lcd, 0, Qt::AlignLeft | Qt::AlignTop);
    this->_ScoreLayout->addWidget(this->_Black->lcd, 0, Qt::AlignRight | Qt::AlignTop);
    this->_ScoreLayout->addWidget(this->_BlackIcon->getImage());
}

Score::~Score()
{

}

QHBoxLayout *Score::getLayout() const
{
    return (this->_ScoreLayout);
}

MyLCD       *Score::getWhite() const
{
    return (this->_White);
}

MyLCD       *Score::getBlack() const
{
    return (this->_Black);
}
