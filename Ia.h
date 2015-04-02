#ifndef IA_H
#define IA_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <utility>
#include <stdint.h>
#include "define.h"
#include "referee.h"
class Ia
{
private:
    uint32_t    **_Map;
    Referee     *_Referee;
    int         _Rules;
    int         min_x;
    int         min_y;
    int         max_x;
    int         max_y;

public:
    Ia(int rules);
    ~Ia();
    void                          initMap();
    void                          affMap();
    uint32_t                      CheckCases(int x, int y);
    std::pair<uint32_t, bool>     CheckRow(int x, int y, int x_i, int y_i, uint32_t p1, uint32_t p2, int type);
    uint32_t                      FillValue(std::pair<uint32_t, bool> pieces, uint32_t value, int mode);
    uint32_t                      CheckMask(uint32_t value, uint32_t mask);
    void                          Update_vision(int x, int y);
    std::pair <int, int>          Play(int x,int y);
    std::pair <int, int>          Get_max_value();
    void                          UpdateMap(int x, int y, int team);
    uint32_t                      CheckEatable(int x, int y, uint32_t value, uint32_t mask, uint32_t p1, uint32_t p2);
    uint32_t                      CheckEat(int x, int y, int x_i, int y_i, uint32_t p1, uint32_t p2, uint32_t mask, uint32_t value);
    uint32_t                      CheckLine(uint32_t value, int x, int y, uint32_t p1, uint32_t p2);
    uint32_t                      CondLine(uint32_t value, std::pair<uint32_t, bool> pieces, int x, int y);
    bool                          AlreadyExist(std::pair<int, int> move);
    bool                          Doublethree(uint32_t **Map, int x, int y, uint32_t team);
    int                           free_three(uint32_t **Map, int x, int y, int xo, int yo, uint32_t team);
    void                          affPiece(uint32_t coord);
    bool                          isCassable(int x, int y, uint32_t p1, uint32_t p2);
    bool                          isCassableEat(int x, int y, int x_i, int y_i, uint32_t p1, uint32_t p2);

};

#endif // IA_H
