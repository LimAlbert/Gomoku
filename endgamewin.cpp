#include "endgamewin.h"
#include <iostream>
#include <QString>
#include <QPushButton>

EndGameWin::EndGameWin(std::list<Piece *> ListPiece, QWidget *parent)
{
    (void)parent;
    this->setWindowTitle("Fin de partie");
    this->setFixedSize(150, 100);
    this->CreateLabel((*ListPiece.begin()));
    this->FillLayout();
    this->Connect();
}

void        EndGameWin::CreateLabel(Piece *_piece)
{
    QString     string(_piece->getString().c_str());
    QString     string2("Victoire de ");

    if (_piece->getTeam() == NOIR)
        string2.append("Noir !");
    else
        string2.append("Blanc !");
    this->_Labelname = new QLabel(string2);
    this->_Label = new QLabel(string);
    this->_Ok = new QPushButton("OK", this);
}

void        EndGameWin::FillLayout()
{
    this->_Layout = new QVBoxLayout;
    this->_Layout->addWidget(this->_Labelname);
    this->_Layout->addWidget(this->_Label);
    this->_Layout->addWidget(this->_Ok);
    this->setLayout(this->_Layout);
}

void        EndGameWin::Connect()
{
    this->connect(this->_Ok, SIGNAL(clicked()), this, SLOT(accept()));
}
