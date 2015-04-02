#ifndef GAME_H
#define GAME_H

#include    <iostream>
#include    <vector>
#include    <list>
#include    <QMouseEvent>
#include    <QtGui>
#include    "define.h"
#include    "image.h"
#include    "goban.h"
#include    "score.h"
#include    "Ia.h"
#include    "referee.h"
#include    "endgamewin.h"

class       Game : public QMainWindow
{
        Q_OBJECT
private:
    Ia                              *_Ia;
    uint32_t                        **_Map;
    std::list<Piece *>              *_Pieces;
    Goban                           *_Goban;
    Score                           *_Score;
    Referee                         *_Referee;
    bool                            _Game;
    int                             _Turn;
    int                             _ScoreW;
    int                             _ScoreB;
    int                             _Gmode;
    int                             _Rules;
    void                            ChangeTurn();
    void                            CreateMap();
    void                            ModifMap(int type, std::list<Piece*>);
    void                            CheckRules();
    void                            ChangePieces(Piece *piece);
    void                            DeletePiece(Piece *piece);
    void                            AffMap();
    void                            EndGame(std::list<Piece *> &);
    void                            IaPlay(int x, int y);
    std::list<Piece *>              ToPieces(std::pair<std::pair<int, int>, std::pair<int, int> >    pairlist);


public:
    Game(QVBoxLayout *&_MainLayout, Score *&score, bool mode, int gmode, int rules);
    Score   *getScore() const;
    ~Game();
private slots:
    void            Play(QMouseEvent *);
};

#endif // GAME_H
