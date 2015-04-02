#include "Ia.h"

Ia::Ia(int rules)
{
    this->initMap();
    this->_Referee = new Referee(this->_Rules);
    this->min_x = -1;
    this->min_y = -1;
    this->max_x = -1;
    this->max_y = -1;
    this->_Rules = rules;
}

Ia::~Ia()
{
    delete this->_Referee;
    if (this->_Map != NULL)
    {
      for(int i = 0; i < 19; i++)
        delete this->_Map[i];
      delete this->_Map;
    }
}

void    Ia::affMap()
{
    for (int i = 0; i != 19; i++)
    {
        for (int j = 0; j != 19; j++)
            std::cout << this->_Map[i][j];
        std::cout << std::endl;
    }
}

void    Ia::initMap()
{
    this->_Map = new uint32_t * [19];
    for (int i = 0; i != 19; i++)
    {
        this->_Map[i] = new uint32_t[19];
        for (int j = 0; j != 19; j++)
          this->_Map[i][j] = 0;
    }
}

bool    Ia::AlreadyExist(std::pair<int, int> move)
{
    if (this->_Map[move.second][move.first] == IA || this->_Map[move.second][move.first] == PLAYER)
        return (true);
    return (false);
}

void    Ia::Update_vision(int x, int y)
{
    if (this->min_x == -1 || (this->min_x + 2) >= x)
        this->min_x = x - 2;
    if (this->min_y == -1 || (this->min_y + 2) >= y)
        this->min_y = y - 2;
    if (this->max_x == -1 || (this->max_x - 2) <= x)
        this->max_x = x + 2;
    if (this->max_y == -1 || (this->max_y - 2) < y)
        this->max_y = y + 2;
    if (this->min_x < 0)
        this->min_x = 0;
    if (this->min_y < 0)
        this->min_y = 0;
    if (this->max_x > 18)
        this->max_x = 18;
    if (this->max_y > 18)
        this->max_y = 18;
}

void                    Ia::affPiece(uint32_t coord)
{
    if ((coord & 2147483648)  == 2147483648)
    {
        std::cout << "blanc peut gagner" << std::endl;
    }
    if ((coord & 1073741824)  == 1073741824)
    {
        std::cout << "Manger une piece de blanc en row 4" << std::endl;
    }
    if ((coord & 536870912)  == 536870912)
    {
        std::cout << "noir peut gagner" << std::endl;
    }
    if ((coord & 268435456)  == 268435456)
    {
        std::cout << "blanc peut aligner un 4 libre" << std::endl;
    }
    if ((coord & 16777216)  == 16777216)
    {
        std::cout << "Manger une piece de blanc en row 3" << std::endl;
    }
    if ((coord & 8388608)  == 8388608)
    {
        std::cout << "noir peut  aligner un 4 libre" << std::endl;
    }
    if ((coord & 4194304)  == 4194304)
    {
        std::cout << "noir peut  aligner un double 3" << std::endl;
    }
    if ((coord & 2097152)  == 2097152)
    {
        std::cout << "blanc peut  aligner un 3 libre" << std::endl;
    }
    if ((coord & 131072)  == 131072)
    {
        std::cout << "blanc peut manger" << std::endl;
    }
    if ((coord & 65536)  == 65536)
    {
        std::cout << "blanc bloque un manger" << std::endl;
    }
    if ((coord & 4096)  == 4096)
    {
        std::cout << "blanc aligne un 4 bloquant" << std::endl;
    }
    if ((coord & 256)  == 256)
    {
        std::cout << "blanc aligne un 2 libre" << std::endl;
    }
    if ((coord & 16)  == 16)
    {
        std::cout << "blanc aligne un 2 bloquant" << std::endl;
    }
    std::cout << "----------" << std::endl;
}

std::pair<int, int>     Ia::Get_max_value()
{
    uint32_t            coord = 0;
    std::pair<int, int> move;

    for (int y = this->min_y; y <= this->max_y; y++)
    {
        for (int x = this->min_x; x <= this->max_x; x++)
        {
            if (this->_Map[y][x] >= coord && (this->_Map[y][x] & 3) == 0)
            {
                if ((this->_Map[y][x] & 16) == 16)
                {
                    if (((coord & 2147483648)  == 2147483648) || ((coord & 536870912)  == 536870912) || ((coord & 8388608)  == 8388608) || ((coord & 4194304)  == 4194304))
                    {
                        coord = this->_Map[y][x];
                        move.first = x;
                        move.second = y;
                    }
                }
                else
                {
                    coord = this->_Map[y][x];
                    move.first = x;
                    move.second = y;
                }
            }
        }
    }
    if (coord == 0)
    {
        do
        {
            move.first  = this->min_x + (rand() % ((this->max_x - this->min_x) + 1));
            move.second = this->min_y + (rand() % ((this->max_y - this->min_y) + 1));
        } while (this->AlreadyExist(move) == true);
    }
    this->UpdateMap(move.first, move.second, IA);
    this->Update_vision(move.first, move.second);
    std::cout << "JE JOUE EN X: " << move.first << " Y: " << move.second << std::endl;
    this->affPiece(coord);
    return (move);
}

int             Ia::free_three(uint32_t **Map, int x, int y, int xo, int yo, uint32_t team)
{
    int         as = 0;
    int         asr = 0;
    uint32_t    previous;
    int         x_bkp = x;
    int         y_bkp = y;
    bool        on_as = false;
    bool        on_asr = false;
    int         line = 1;

    for (int i = 0; i < 4; ++i)
    {
        if (x == 18 || x == 0 || y == 0 || y == 18)
            return (0);
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
            if (previous == team)
                as = 0;
        }
    }
    x = x_bkp;
    y = y_bkp;
    for (int i = 0; i < 4; ++i)
    {
        if (x == 18 || x == 0 || y == 0 || y == 18)
            return (0);
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
            if (previous == team)
                asr = 0;
        }
    }
    if ((line + as) >= 3 || (line + asr) >= 3)
        return (1);
    return (0);
}

bool        Ia::Doublethree(uint32_t **Map, int x, int y, uint32_t team)
{
    int     three = 0;

    if (x == 18 || x == 0 || y == 0 || y == 18)
        return (true);
    three += free_three(Map, x, y, 1, 0, team);
    three += free_three(Map, x, y, -1, -1, team);
    three += free_three(Map, x, y, 0, -1, team);
    three += free_three(Map, x, y, 1, -1, team);
    if (three >= 2)
        return (false);
    return (true);
}

bool                                      Ia::isCassableEat(int x, int y, int x_i, int y_i, uint32_t p1, uint32_t p2)
{
    int                                   x_bkp = x;
    int                                   y_bkp = y;

    x = x_bkp + x_i;
    y = y_bkp + y_i;
    if (x >= 0 && x <= 18 && y >= 0 && y <= 18 && this->_Map[y][x] == p2)
    {
        x_i *= -1;
        y_i *= -1;
        x = x_bkp + x_i;
        y = y_bkp + y_i;
        if (x >= 0 && x <= 18 && y >= 0 && y <= 18 && this->_Map[y][x] == p1)
        {
            x = x_bkp + x_i;
            y = y_bkp + y_i;
            if (x >= 0 && x <= 18 && y >= 0 && y <= 18 && (this->_Map[y][x] & 3) == 0)
                return (true);
        }
    }
    return (false);
}

bool                                      Ia::isCassable(int x, int y, uint32_t p1, uint32_t p2)
{
    if (this->isCassableEat(x, y, 1, 0, p1, p2) == true)
        return (true);
    if (this->isCassableEat(x, y, 0, 1, p1, p2) == true)
        return (true);
    if (this->isCassableEat(x, y, 1, 1, p1, p2) == true)
        return (true);
    if (this->isCassableEat(x, y, 1, -1, p1, p2) == true)
        return (true);
    //check  toutes les directions si y'a une piece blanche
    //si piece blanche, regarder si apres noire + vide
    return (false);
}

std::pair<uint32_t, bool>                 Ia::CheckRow(int x, int y, int x_i, int y_i, uint32_t p1, uint32_t p2, int type)
{
    std::pair<uint32_t, bool>             count;
    bool                                  space = false;
    int                                   x_bkp = x;
    int                                   y_bkp = y;

    x = x_bkp + x_i;
    y = y_bkp + y_i;
    count.first = 0;
    count.second = false;
    if (x_bkp == 0 && y_bkp == 4 && p1 == PLAYER)
        std::cout << "PUTAIN X: " << x << " Y: " << y << std::endl;
    while (x >= 0 && x <= 18 && y >= 0 && y <= 18 && this->_Map[y][x] == p1)
    {
        if (x_bkp == 0 && y_bkp == 4 && p1 == PLAYER)
            std::cout << "je suis dedans lol " << count.first << std::endl;
        //evaluer la case pour savoir si c'est mangeable
        if (((this->_Referee->getRules() & 1) == 1) && this->isCassable(x, y, p1, p2) == true)
        {
            std::cout << "5 bloquant" <<std::endl;
            count.second = true;
            break;
        }
        count.first++;
        x += x_i;
        y += y_i;
        if (type == 1 && x >= 0 && x <= 18 && y >= 0 && y <= 18 && space == false && (this->_Map[y][x] & 3) == 0)
        {
            space = true;
            x += x_i;
            y += y_i;
        }
    }
    if ((x < 0 || x > 18 || y < 0 || y > 18) || (x >= 0 && x <= 18 && y >= 0 && y <= 18 && this->_Map[y][x] == p2))
        count.second = true;
    space = false;
    x_i *= -1;
    y_i *= -1;
    x = x_bkp + x_i;
    y = y_bkp + y_i;
    while (x >= 0 && x <= 18 && y >= 0 && y <= 18 && this->_Map[y][x] == p1)
    {
        if (((this->_Referee->getRules() & 1) == 1) && this->isCassable(x, y, p1, p2) == true)
        {
            count.second = true;
            break;
        }
        count.first++;
        x += x_i;
        y += y_i;
        if (type == 1 && x >= 0 && x <= 18 && y >= 0 && y <= 18 && space == false && (this->_Map[y][x] & 3) == 0)
        {
            space = true;
            x += x_i;
            y += y_i;
        }
    }

    if ((((count.first != 4) && (count.first != 3)) || count.second != true) && ((x < 0 || x > 18 || y < 0 || y > 18) || (x >= 0 && x <= 18 && y >= 0 && y <= 18 && this->_Map[y][x] == p2)))
    {
        if (count.second == true)
            count.first = 0;
        else
            count.second = true;
    }
    return (count);
}

uint32_t                        Ia::CheckMask(uint32_t value, uint32_t mask)
{
    while ((value & mask) != 0)
        mask = mask >> 1;
    value = value | mask;
    return (value);
}

uint32_t                        Ia::FillValue(std::pair<uint32_t, bool> pieces, uint32_t value, int mode)
{
    if (mode == 1)
    {
        if (pieces.first >= 4)
            value = value | 2147483648;// combinaison gagnante
        else if (pieces.first == 3)
        {
            if (pieces.second == false)
                value = this->CheckMask(value, 268435456);//4 libre
            else
                value = this->CheckMask(value, 4096);//4 non libre
        }
        else if (pieces.first == 2)
        {
            if (pieces.second == false)
                value = this->CheckMask(value, 2097152);//3 libre
            else
                value = this->CheckMask(value, 65536);//3 non libre = bloque un manger
        }
        else if (pieces.first == 1)
        {
            if (pieces.second == false)
                value = this->CheckMask(value, 256);//2 libre
            else
                value = value | 16; //2 non libre (malus a voir)
        }
    }
    else
    {
        if (pieces.first >= 4)
            value = value | 536870912;
        else if (pieces.first == 3 && pieces.second == false)
            value = value | 8388608;
    }
    return (value);
}

uint32_t                            Ia::CondLine(uint32_t value, std::pair<uint32_t, bool> pieces, int x, int y)
{
    if ((pieces.first + 1) >= 4)
        value = (value | 1073741824);
    else if ((pieces.first + 1) == 3 && pieces.second == false)
        value = (value | 16777216);
    return (value);
}

uint32_t                            Ia::CheckLine(uint32_t value, int x, int y, uint32_t p1, uint32_t p2)
{
    std::pair<uint32_t, bool>       pieces;

    pieces = this->CheckRow(x, y, 1, 0, p2, p1, 2); // PLAYER POUR TEST, INVERSER ENSUITE
    value = this->CondLine(value, pieces,x ,y);
    pieces = this->CheckRow(x, y, 0, 1, p2, p1, 2);
    value = this->CondLine(value, pieces,x,y);
    pieces = this->CheckRow(x, y, 1, 1, p2, p1, 2);
    value = this->CondLine(value, pieces,x,y);
    pieces = this->CheckRow(x, y, 1, -1, p2, p1, 2);
    value = this->CondLine(value, pieces,x,y);
    return (value);
}

uint32_t                            Ia::CheckEat(int x, int y, int x_i, int y_i, uint32_t p1, uint32_t p2, uint32_t mask, uint32_t value)
{
    int                             count = 0;
    int                             i = 0;
    int                             x_bkp = x;
    int                             y_bkp = y;

    x = x_bkp + x_i;
    y = y_bkp + y_i;
    while (i != 3)
    {
        if (i == 2 && count == 2 && x >= 0 && x <= 18 && y >= 0 && y <= 18 && this->_Map[y][x] == p1)
        {
            value = (value | mask);
            value = this->CheckLine(value, (x - x_i), (y - y_i), p1, p2);
            value = this->CheckLine(value, (x -  (x_i * 2)), (y - (y_i * 2)), p1, p2);
        }
        if (x >= 0 && x <= 18 && y >= 0 && y <= 18 && this->_Map[y][x] == p2)
            count++;
        x += x_i;
        y += y_i;
        i++;
    }
    i = 0;
    count = 0;
    x_i *= -1;
    y_i *= -1;
    x = x_bkp + x_i;
    y = y_bkp + y_i;
    while (i != 3)
    {
        if (i == 2 && count == 2 && x >= 0 && x <= 18 && y >= 0 && y <= 18 && this->_Map[y][x] == p1)
        {
            value = (value | mask);
            value = this->CheckLine(value, (x - x_i), (y - y_i), p1, p2);
            value = this->CheckLine(value, (x -  (x_i * 2)), (y - (y_i * 2)), p1, p2);
        }
        if (x >= 0 && x <= 18 && y >= 0 && y <= 18 && this->_Map[y][x] == p2)
            count++;
        x += x_i;
        y += y_i;
        i++;
    }
    return (value);
}

uint32_t                            Ia::CheckEatable(int x, int y, uint32_t value, uint32_t mask, uint32_t p1, uint32_t p2)
{
    value = this->CheckEat(x, y, 1, 0, p1, p2, mask, value);
    value = this->CheckEat(x, y, 0, 1, p1, p2, mask, value);
    value = this->CheckEat(x, y, 1, 1, p1, p2, mask, value);
    value = this->CheckEat(x, y, 1, -1, p1, p2, mask, value);
    return (value);
}

uint32_t                            Ia::CheckCases(int x, int y)
{
    std::pair<uint32_t, bool>       pieces;
    uint32_t                        value = 0;

    pieces = this->CheckRow(x, y, 1, 0, IA, PLAYER, 1); // PLAYER POUR TEST, INVERSER ENSUITE
    value = this->FillValue(pieces, value, 1);
    pieces = this->CheckRow(x, y, 0, 1, IA, PLAYER, 1);
    value = this->FillValue(pieces, value, 1);
    pieces = this->CheckRow(x, y, 1, 1, IA, PLAYER, 1);
    value = this->FillValue(pieces, value, 1);
    pieces = this->CheckRow(x, y, 1, -1, IA, PLAYER, 1);
    value = this->FillValue(pieces, value, 1);

    value = this->CheckEatable(x, y, value, 131072, IA, PLAYER); // PLAYER POUR TEST, INVERSER ENSUITE

    pieces = this->CheckRow(x, y, 1, 0, PLAYER, IA, 1); // IA POUR TEST, INVERSER ENSUITE
    value = this->FillValue(pieces, value, 2);
    pieces = this->CheckRow(x, y, 0, 1, PLAYER, IA, 1);
    value = this->FillValue(pieces, value, 2);
    pieces = this->CheckRow(x, y, 1, 1, PLAYER, IA, 1);
    value = this->FillValue(pieces, value, 2);
    pieces = this->CheckRow(x, y, 1, -1, PLAYER, IA, 1);
    value = this->FillValue(pieces, value, 2);
    if (this->Doublethree(this->_Map, x, y, PLAYER) == false) // PLAYER POUR TEST, INVERSER ENSUITE
    {
        std::cout << "JAI TROUVE UN DOUBLE TROIS x: " << x << " y: " << y << std::endl;
        value |= 4194304;
    }
    if (((this->_Referee->getRules() & 2) == 2) && this->Doublethree(this->_Map, x, y, IA) == false) // PLAYER POUR TEST, INVERSER ENSUITE
    {
        std::cout << "JE NE JOUE PAS DOUBLE TROIS x: " << x << " y: " << y << std::endl;
        value = 0;
    }
//    if (pieces.first > 0)
//        std::cout << "x: " << x << " y " << y << " bloque " << pieces.second << " PIECE: " << pieces.first << std::endl;
   // std::cout << "VALUE " << value << std::endl;
    return (value);
}

void                    Ia::UpdateMap(int x, int y, int team)
{
    std::pair<std::pair<int, int>, std::pair<int, int> >    pairlist;

    this->_Map[y][x] = team;
    pairlist = this->_Referee->Toeat(this->_Map, x, y, team);
    if (pairlist.first.first != 0 || pairlist.first.second != 0)
    {
        std::cout << "COUCOU, JE MANGE X: " << pairlist.first.first;
        if ((pairlist.first.second & M_P1) == M_P1)
            std::cout << " ET Y: " << (pairlist.first.second ^ M_P1) << std::endl;
        else if ((pairlist.first.second & M_P2) == M_P2)
            std::cout << " ET Y: " << (pairlist.first.second ^ M_P2) << std::endl;
        if ((pairlist.first.second & M_P1) == M_P1)
            this->_Map[pairlist.first.second ^ M_P1][pairlist.first.first] = 0;
        else if ((pairlist.first.second & M_P2) == M_P2)
            this->_Map[pairlist.first.second ^ M_P2][pairlist.first.first] = 0;
        if ((pairlist.second.second & M_P1) == M_P1)
            this->_Map[pairlist.second.second ^ M_P1][pairlist.second.first] = 0;
        else if ((pairlist.second.second & M_P2) == M_P2)
            this->_Map[pairlist.second.second ^ M_P2][pairlist.second.first] = 0;
    }
    if (team == PLAYER)
    {
        for (int y = this->min_y; y <= this->max_y; y++)
        {
            for (int x = this->min_x; x <= this->max_x; x++)
            {
                if ((this->_Map[y][x] & 3) == 0)
                {
                    this->_Map[y][x] = this->CheckCases(x, y);
                }
            }
        }
    }
}

std::pair<int, int>     Ia::Play(int x, int y)
{
    std::pair <int, int>     move;

    this->Update_vision(x, y);
   /* std::cout << "MIN X " << this->min_x << std::endl;
    std::cout << "MAX_X "  << this->max_x << std::endl;
    std::cout << "MIN_Y " << this->min_y << std::endl;
    std::cout << "Max_Y " << this->max_y << std::endl;*/
  //  std::cout << "update map" << std::endl;
    this->UpdateMap(x, y, PLAYER);
  //  std::cout << "get max value" << std::endl;
    move = Get_max_value();

/*    std::cout << "MOVE X: " << move.first << std::endl;
    std::cout << "MOVE Y: " << move.second << std::endl; */
    return (move);
}
