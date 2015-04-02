#ifndef ENDGAMEWIN_H
#define ENDGAMEWIN_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <list>
#include "piece.h"

class EndGameWin : public QDialog
{
private:
    QPushButton     *_Ok;
    QVBoxLayout     *_Layout;
    QLabel          *_Label;
    QLabel          *_Labelname;
    void            CreateLabel(Piece *_piece);
    void            FillLayout();
    void            Connect();

public:
    EndGameWin(std::list<Piece *> ListPiece, QWidget *parent = 0);
};

#endif // ENDGAMEWIN_H
