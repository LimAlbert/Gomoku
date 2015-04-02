#include "newgameslot.h"
#include <iostream>

NewGameSlot::NewGameSlot(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Nouvelle Partie");
    this->setFixedSize(250, 200);
    this->CreateRadioLayout();
    this->CreateCheckLayout();
    this->CreateButtonsLayout();
    this->ConnectActions();
    this->MergeLayouts();
}

void    NewGameSlot::ConnectActions()
{
    this->connect(this->ok, SIGNAL(clicked()), this, SLOT(accept()));
    this->connect(this->cancel, SIGNAL(clicked()), this, SLOT(close()));
}

void    NewGameSlot::CreateCheckLayout()
{
    this->_CheckLayout = new QHBoxLayout;
    this->_Check = new QGroupBox("Regles du jeu", this);
    this->_Cinq = new QCheckBox("Cinq cassable", this);
    this->_Double = new QCheckBox("Double trois", this);
    this->_CheckLayout->addWidget(this->_Cinq);
    this->_CheckLayout->addWidget(this->_Double);
    this->_Check->setLayout(this->_CheckLayout);
}

void    NewGameSlot::CreateRadioLayout()
{
    this->_RadiosLayout = new QHBoxLayout;
    this->_Radios = new QGroupBox("Mode de jeu", this);
    this->_Jvj = new QRadioButton("Joueur vs Joueur");
    this->_Jvia = new QRadioButton("Joueur vs IA");
    this->_Jvj->setChecked(true);
    this->_RadiosLayout->addWidget(this->_Jvj);
    this->_RadiosLayout->addWidget(this->_Jvia);
    this->_Radios->setLayout(this->_RadiosLayout);
}

void    NewGameSlot::CreateButtonsLayout()
{
    this->boutons = new QHBoxLayout;

    this->ok = new QPushButton("OK", this);
    this->cancel = new QPushButton("Annuler", this);
    this->boutons->addWidget(this->ok);
    this->boutons->addWidget(this->cancel);
}

void    NewGameSlot::MergeLayouts()
{
    this->layout = new QVBoxLayout;
    this->layout->addWidget(this->_Radios);
    this->layout->addWidget(this->_Check);
    this->layout->addLayout(this->boutons);
    this->setLayout(this->layout);
}

int    NewGameSlot::getMode() const
{
    if (this->_Jvj->isChecked())
        return (0);
    else
        return (1);
}

int     NewGameSlot::getRules() const
{
    int ret = 0;

    if (this->_Cinq->isChecked())
        ret |= 1;
    if (this->_Double->isChecked())
        ret |= 2;
    return (ret);
}

