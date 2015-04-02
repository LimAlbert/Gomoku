#include "interface.h"

Interface::Interface()
{
    this->setFixedSize(592, 652);
    this->CreateMenu();
    this->setWindowTitle("Gomoku");
    this->_MainArea = new QWidget;
    this->_MainLayout = new QVBoxLayout;
    setCentralWidget(this->_MainArea);
    this->_MainArea->setLayout(this->_MainLayout);
    this->_Score = new Score(this);
    this->_MainLayout->addLayout(this->_Score->getLayout());
    this->CurrentGame = new Game(this->_MainLayout, this->_Score, false, 0, 0);
}

void    Interface::CreateMenu()
{
    this->File = menuBar()->addMenu("&Fichier");
    this->New = this->File->addAction("&Nouvelle Partie");
    this->Quit = this->File->addAction("&Quitter");
    this->ConnectActions();
    this->SetShortcuts();
}

Interface::~Interface()
{

}

void    Interface::ConnectActions()
{
    this->connect(this->Quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    this->connect(this->New, SIGNAL(triggered()), this, SLOT(NewGameWin()));
}

void    Interface::SetShortcuts()
{
    this->Quit->setShortcut(QKeySequence("Ctrl+Q"));
    this->New->setShortcut(QKeySequence("Ctrl+N"));
}

void    Interface::remove(QLayout* layout)
{
    QLayoutItem* child;
    while((child = layout->takeAt(1)) != 0)
    {
        if(child->layout() != 0)
        {
            remove(child->layout());
        }
        else if(child->widget() != 0)
        {
            delete child->widget();
        }

        delete child;
    }
}

void    Interface::NewGameWin()
{
    NewGameSlot *NewGame = new NewGameSlot(this);

    if (NewGame->exec() == QDialog::Accepted)
    {
        this->remove(this->_MainLayout);
        this->CurrentGame->getScore()->getWhite()->lcd->display(0);
        this->CurrentGame->getScore()->getBlack()->lcd->display(0);
        delete this->CurrentGame;
        this->_Mode = NewGame->getMode();
        this->_Rules = NewGame->getRules();

        this->CurrentGame = new Game(this->_MainLayout, this->_Score, true, this->_Mode, this->_Rules);
    }
}
