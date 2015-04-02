#ifndef INTERFACE_H
#define INTERFACE_H

#include <QtWidgets/QMainWindow>
#include <QtGui>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QLabel>
#include "mylcd.h"
#include "image.h"
#include "game.h"
#include "score.h"
#include "newgameslot.h"

class       Interface : public QMainWindow
{
    Q_OBJECT
private:
    QWidget     *_MainArea;
    QVBoxLayout *_MainLayout;
    QMenu       *File;
    QAction     *Quit;
    QAction     *New;
    Game        *CurrentGame;
    Score       *_Score;
    int         _Mode;
    int         _Rules;
    void        ConnectActions();
    void        SetShortcuts();
    void        CreateMenu();
    void        remove(QLayout* layout);

public:
    Interface();
    ~Interface();

public slots:
    void    NewGameWin();
};

#endif // INTERFACE_H
