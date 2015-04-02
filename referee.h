#ifndef REFEREE_H
#define REFEREE_H

#include <list>
#include <vector>
#include <iostream>
#include "piece.h"

typedef struct  s_index
{
    int x;
    int y;
    int ix;
    int iy;
}               t_index;

class Referee
{
private:
    int                 _Rules;
    int                 _WinTeam;

public:
    Referee(int);
    bool                isMovePossible(uint32_t **, Piece *&);
    std::list<Piece *>  isEvent(uint32_t **, Piece *&, int, int);
    bool                CheckEnd(uint32_t **, Piece *&);
    bool                AlreadyPiece(uint32_t **, Piece *&);
    bool                CheckIsEatable(uint32_t **, int, int, uint32_t, int);
    bool                CheckPieceSide(uint32_t **, int x, int y, int type);
    bool                CheckCinq(uint32_t **, int, int, int, int, int, int);
    bool                CheckEndH(int, int, uint32_t, uint32_t **, int);
    bool                CheckPieces(int, int);
    bool                Doublethree(uint32_t **, int x, int y, uint32_t team);
    int                 free_three(uint32_t **, int x, int y, int xo, int yo, uint32_t team);
    std::pair<std::pair<int, int>, std::pair<int, int> >     Toeat(uint32_t   **Map, int x, int y, uint32_t team);
    int                 getRules() const;
    //std::list<Piece *>  Toeat(uint32_t   **Map, Piece *&_Piece);

};

#endif // REFEREE_H
