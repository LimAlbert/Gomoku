#include "referee.h"



Referee::Referee(int Rules)
{
    this->_Rules = Rules;
}

std::pair<std::pair<int, int>, std::pair<int, int> >     Referee::Toeat(uint32_t   **Map, int x, int y, uint32_t team)
{
    std::pair<std::pair<int, int>, std::pair<int, int> > list;
    uint32_t                                             team2;
    int                                                  x_bkp = x;
    int                                                  y_bkp = y;
    t_index ieat[8] = {
    {-3, 0, 1, 0},
    {-3, -3, 1, 1},
    {0,-3, 0, 1},
    {3,-3,-1, 1},
    {3, 0, -1, 0},
    {3, 3, -1, -1},
    {0, 3, 0, -1},
    {-3, 3, 1, -1}
    };

    list.first.first = 0;
    list.first.second = 0;
    if (team == NOIR)
        team2 = BLANC;
    else
        team2 = NOIR;
    //std::cout << "TOEAT X: " << x << " Y: " << y << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        x = x_bkp + ieat[i].x;
        y = y_bkp + ieat[i].y;
        if (x >= 0 && x <= 18 &&  y >= 0 && y <= 18)
        {
            if (Map[y][x] == team)
            {
                if ((Map[y + ieat[i].iy][x + ieat[i].ix] == team2)
                        && (Map[y + (ieat[i].iy * 2)][x + (ieat[i].ix * 2)] == team2))
                {
                    list.first.first = x + ieat[i].ix;
                    if (team == NOIR)
                     {
                        list.first.second = (y + ieat[i].iy) | M_P1;
                        std::cout << "TOEAT X: " << x + ieat[i].ix << " Y: " << (((y + ieat[i].iy) | M_P1) ^ M_P1) << std::endl;

                    }
                    else
                        list.first.second = (y + ieat[i].iy) | M_P2;
                    list.second.first = x + (ieat[i].ix * 2);
                    if (team == NOIR)
                    {
                        std::cout << "TOEAT2 X: " << x + (ieat[i].ix * 2) << " Y: " << (((y + (ieat[i].iy * 2)) | M_P1) ^ M_P1) << std::endl;
                        list.second.second = (y + (ieat[i].iy * 2)) | M_P1;
                    }
                    else
                        list.second.second = (y + (ieat[i].iy * 2)) | M_P2;
                }
            }
        }
    }
    return (list);
}

bool        Referee::AlreadyPiece(uint32_t **Map, Piece *&_Piece)
{
    if (Map[_Piece->getY() / 30][_Piece->getX() / 30] != 0)
        return (false);
    return (true);
}

int         Referee::free_three(uint32_t **Map, int x, int y, int xo, int yo, uint32_t team)
{
    int         as = 0;
    int         asr = 0;
    uint32_t    previous;
    int         x_bkp = x;
    int         y_bkp = y;
    bool        on_as = false;
    bool        on_asr = false;
    int         line = 1;
    int         block = 0;

    for (int i = 0; i < 4; ++i)
    {
        if (x == 18 || x == 0 || y == 0 || y == 18)
            return 0;
        previous = Map[y][x];
        x += xo;
        y += yo;
        if (Map[y][x] == team && on_as == false)
            line += 1;
        else if (Map[y][x] == team && on_as == true)
            as += 1;
        else if (Map[y][x] == 0)
        {
            if(on_as == false)
                on_as = true;
            else
                break;
        }
        else
        {
            if (on_as == false)
                return (0);
            else
                block += 0.5;
            if (previous == team)
                as = 0;
        }
    }
    x = x_bkp;
    y = y_bkp;
    for (int i = 0; i < 4; ++i)
    {
        if (x == 18 || x == 0 || y == 0 || y == 18)
            return 0;
        previous = Map[y][x];
        x += (xo * -1);
        y += (yo * -1);
        if (Map[y][x] == team && on_asr == false)
            line += 1;
        else if (Map[y][x] == team && on_asr == true)
            asr += 1;
        else if (Map[y][x] == 0)
        {
            if(on_asr == false)
                on_asr = true;
            else
                break;
        }
        else
        {
            if (on_asr == false)
                return (0);
            else
                block += 0.5;
            if (previous == team)
                asr = 0;
        }
    }
    if (line == 4 || line == 5)
        return 0;
    if ((line + as) >= 3 || (line + asr) >= 3)
        return 1;
    return 0;
}

bool        Referee::Doublethree(uint32_t **Map, int x, int y, uint32_t team)
{
    int     three = 0;

    if (x == 18 || x == 0 || y == 0 || y == 18)
        return true;
    three += free_three(Map, x, y, 1, 0, team);
    three += free_three(Map, x, y, -1, -1, team);
    three += free_three(Map, x, y, 0, -1, team);
    three += free_three(Map, x, y, 1, -1, team);
    if (three >= 2)
        return false;
    return true;
}

bool        Referee::isMovePossible(uint32_t **Map, Piece *&_Piece)
{
    (void)Map;
    (void)_Piece;
    if (this->AlreadyPiece(Map, _Piece) == false)
        return (false);
    if ((this->_Rules & 2) == 2)
    {
        if (this->Doublethree(Map, _Piece->getX() / 30, _Piece->getY() / 30, _Piece->getTeam()) == false)
            return (false);
    }
    return (true);
}

int         Referee::getRules() const
{
    return (this->_Rules);
}

bool        Referee::CheckIsEatable(uint32_t **Map, int x, int y, uint32_t team, int type)
{
    if (team == NOIR)
        team = BLANC;
    else if (team == BLANC)
        team = NOIR;
    if (type == 1)
    {
        if (((y - 1 >= 0) && Map[y - 1][x] == team) && ((y + 2 <= 18) && Map[y + 2][x] == 0))
            return (true);
        else if (((y + 2 <= 18) && Map[y + 2][x] == team) && ((y - 1 >= 0) && Map[y - 1][x] == 0))
            return (true);
    }
    else if (type == 2)
    {
        if (((x - 1 >= 0) && Map[y][x - 1] == team) && ((x + 2 <= 18) && Map[y][x + 2] == 0))
            return (true);
        else if (((x + 2 <= 18) && Map[y][x + 2] == team) && ((x - 1 >= 0) && Map[y][x - 1] == 0))
            return (true);
    }
    return (false);
}

bool        Referee::CheckPieceSide(uint32_t **Map, int x, int y, int type)
{
    uint32_t     team;
    bool        ret;
    int         yb;
    int         xb;

    xb = x;
    yb = y;
    team = Map[y][x];
    if ((type != 2) && ((y - 1 >= 0) && ((Map[y - 1][x] == team) || ((y + 1 <= 18) && Map[y + 1][x] == team))))
    {
        if (((y - 1 >= 0) && Map[y - 1][x] == team))
            yb = y - 1;
        ret = this->CheckIsEatable(Map, x, yb, team, 1);
        if (ret == true)
          return (ret);
    }
    else if ((type != 1) && ((x - 1 >= 0) && ((Map[y][x - 1] == team) || ((x + 1 <= 18) && Map[y][x + 1] == team))))
    {
        if (((x - 1 >= 0) && Map[y][x - 1] == team))
            xb = x - 1;
        ret = this->CheckIsEatable(Map, xb, y, team, 2);
        if (ret == true)
          return (ret);
    }
    return (false);
}

bool        Referee::CheckCinq(uint32_t **Map, int left, int x, int y, int xi, int yi, int type)
{
    int     px = x - (left * xi);
    int     py = y - (left * yi);

    left = 0;
    if ((this->_Rules & 1) == 1)
    {
        while (left != 5)
        {
            if (this->CheckPieceSide(Map, px, py, type) == true)
                return (false);
            px += xi;
            py += yi;
            left++;
        }
    }
    return (true);
}

bool        Referee::CheckEndH(int x, int y, uint32_t team, uint32_t **Map, int type)
{
    int     left = 0;
    int     right = 0;
    int     x_bkp = x;
    int     y_bkp = y;

    x = (type == 1 || type == 3 || type == 4) ? x_bkp - 1 : x_bkp;
    y = (type == 2 || type == 4) ? y_bkp - 1 : ((type == 3) ? y_bkp + 1 : y_bkp);
    while (left != 4 && (x >= 0 && x <= 18) && (y >= 0 && y <= 18) && Map[y][x] == team)
    {
        if (Map[y][x] == team)
            left++;
        x = (type == 1 || type == 3 || type == 4) ? x - 1 : x;
        y = (type == 2 || type == 4) ? y - 1 : ((type == 3) ? y + 1 : y);
    }
    x = (type == 1 || type == 3 || type == 4) ? x_bkp + 1 : x_bkp;
    y = (type == 2 || type == 4) ? y_bkp + 1 : ((type == 3) ? y_bkp - 1 : y_bkp);
    while (right != 4 && (x >= 0 && x <= 18) && (y >= 0 && y <= 18) && Map[y][x] == team)
    {
        if (Map[y][x] == team)
            right++;
        x = (type == 1 || type == 3 || type == 4) ? x + 1 : x;
        y = (type == 2 || type == 4) ? y + 1 : ((type == 3) ? y - 1 : y);
    }
    if (right + left >= 4)
    {
        if (type == 1)
            return (this->CheckCinq(Map, left, x_bkp, y, 1, 0, 1));
        else if (type == 2)
            return (this->CheckCinq(Map, left, x, y_bkp, 0, 1, 2));
        else if (type == 3)
            return (this->CheckCinq(Map, left, x_bkp, y_bkp, 1, -1, 3));
        else if (type == 4)
            return (this->CheckCinq(Map, left, x_bkp, y_bkp, 1, 1, 3));
    }
    return (false);
}

bool        Referee::CheckEnd(uint32_t **Map, Piece *&Piece)
{
    int     x = Piece->getX() / 30;
    int     y = Piece->getY() / 30;
    int     team = Piece->getTeam();

    if (this->CheckEndH(x, y, team, Map, 1) == true || this->CheckEndH(x, y, team, Map, 2) == true ||
        this->CheckEndH(x, y, team, Map, 3) == true || this->CheckEndH(x, y, team, Map, 4) == true)
        return (true);
    return (false);
}

bool        Referee::CheckPieces(int BlackP, int WhiteP)
{
    if (BlackP >= 10)
    {
        this->_WinTeam = NOIR;
        return (true);
    }
    else if (WhiteP >= 10)
    {
        this->_WinTeam = BLANC;
        return (true);
    }
    return (false);
}

std::list<Piece *>              Referee::isEvent(uint32_t **Map, Piece *&_Piece, int BlackP, int WhiteP)
{
    std::list<Piece *>          ListRet;

    if (this->CheckEnd(Map, _Piece) == true)
    {
        Piece *EndPiece = new Piece(_Piece->getTeam(), "Enchainement de 5 pions");
        ListRet.push_back(EndPiece);
    }
    else if (this->CheckPieces(BlackP, WhiteP) == true)
    {
        Piece *EndPiece = new Piece(this->_WinTeam, "Prise de 10 pieces");
        ListRet.push_back(EndPiece);
    }
   return (ListRet);
}
