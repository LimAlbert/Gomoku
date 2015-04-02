#include "game.h"
#include <time.h>
#include <iostream>

Game::Game(QVBoxLayout *&_MainLayout, Score *&score, bool mode, int gmode, int rules)
{
    this->_Pieces = new std::list<Piece *>;
    this->_Score = score;
    this->_ScoreB = 0;
    this->_ScoreW = 0;
    this->_Game = true;
    this->_Turn = NOIR;
    this->_Gmode = gmode;
    this->_Rules = rules;
    this->_Map = NULL;
    this->_Goban = new Goban();
    _MainLayout->addWidget(this->_Goban->GetVue());
    if (mode == true)
    {
        srand(time(NULL));
        this->_Score->getBlack()->lcd->setStyleSheet("background-color: rgb(183,240,208)");
        if (this->_Gmode == 1)
            this->_Ia = new Ia(this->_Rules);
        this->_Referee = new Referee(this->_Rules);
        this->CreateMap();
        this->connect(this->_Goban->GetVue(), SIGNAL(clicked(QMouseEvent *)), this, SLOT(Play(QMouseEvent *)));
    }
}

Game::~Game()
{
    delete this->_Pieces;
    delete this->_Goban;
    delete this->_Referee;
    if (this->_Map != NULL)
    {
      for(int i = 0; i < 19; i++)
        delete this->_Map[i];
      delete this->_Map;
    }
}

void            Game::CheckRules()
{
    if ((this->_Rules & 1) == 1)
        std::cout << "Cinq cassable active" << std::endl;
    if ((this->_Rules & 2) == 2)
        std::cout << "Double Trois active" << std::endl;
}

void            Game::CreateMap()
{
    this->_Map = new uint32_t * [19];
    for (int i = 0; i != 19; i++)
    {
        this->_Map[i] = new uint32_t[19];
        for (int j = 0; j != 19; j++)
          this->_Map[i][j] = 0;
    }
}

void            Game::ChangeTurn()
{
    if (this->_Turn == NOIR)
    {
        this->_Turn = BLANC;
        this->_Score->getWhite()->lcd->setStyleSheet("background-color: rgb(183,240,208)");
        this->_Score->getBlack()->lcd->setStyleSheet("background-color: white");
    }
    else
    {
        this->_Turn = NOIR;
        this->_Score->getBlack()->lcd->setStyleSheet("background-color: rgb(183,240,208)");
        this->_Score->getWhite()->lcd->setStyleSheet("background-color: white");
    }
}

void            Game::ChangePieces(Piece *piece)
{
    if (piece->getTeam() == NOIR)
    {
        this->_ScoreB++;
        this->_Score->getBlack()->lcd->display(this->_ScoreB);
    }
    else
    {
        this->_ScoreW++;
        this->_Score->getWhite()->lcd->display(this->_ScoreW);
    }
}

void            Game::DeletePiece(Piece *piece)
{
     std::list<Piece *>::iterator it;
     std::list<Piece *>::iterator it2;

     for (it = this->_Pieces->begin(); (it != this->_Pieces->end()) && ((*it)->getX() != piece->getX() || (*it)->getY() != piece->getY()); it++);
     this->_Pieces->erase(it);
     delete ((*it)->getItem());
}

void            Game::ModifMap(int type, std::list<Piece*> pieces)
{
  std::list<Piece*>::iterator it;

    if (type == ADD)
    {
        for (it = pieces.begin(); it != pieces.end(); it++ )
        {
            this->_Map[((*it)->getY())/30][((*it)->getX())/30] = (*it)->getTeam();
            this->_Pieces->push_back((*it));
        }
    }
    else
    {
        for (it = pieces.begin(); it != pieces.end(); it++ )
        {
            std::cout << "JE DELETE: " << ((*it)->getX()/30) << " ET " << (((*it)->getY())/30) << std::endl;
            this->_Map[((*it)->getY())/30][((*it)->getX())/30] = 0;
            this->ChangePieces(*it);
            this->DeletePiece(*it);
        }
    }
}

void            Game::AffMap()
{
    for (int i = 0; i != 19; i++)
    {
        for (int j = 0; j != 19; j++)
        {
            std::cout << this->_Map[i][j];
        }
        std::cout << std::endl;
    }
}

void            Game::IaPlay(int x, int y)
{
    std::pair<int, int>     coord;
    std::pair<std::pair<int, int>, std::pair<int, int> >    pairlist;

    coord = this->_Ia->Play(x, y);
    Piece *piece = new Piece(this->_Turn, coord.first * 30, coord.second * 30, this->_Goban->_Scene);
    std::list<Piece*>    PieceList;
    PieceList.push_back(piece);
    this->ModifMap(ADD, PieceList);
    this->ChangeTurn();
    pairlist = this->_Referee->Toeat(this->_Map, coord.first, coord.second, IA);
    PieceList = this->ToPieces(pairlist);
    //PieceList = this->_Referee->Toeat(this->_Map, piece);

    if (PieceList.size() != 0)
        this->ModifMap(DEL, PieceList);
    PieceList = this->_Referee->isEvent(this->_Map, piece, this->_ScoreB, this->_ScoreW);
    if (PieceList.size() == 1)
        this->EndGame(PieceList);
}

std::list<Piece *>      Game::ToPieces(std::pair<std::pair<int, int>, std::pair<int, int> >    pairlist)
{
    std::list<Piece*>    PieceList;
    Piece               *piece;
    Piece               *piece2;

    if (pairlist.first.first != 0 || pairlist.first.second != 0)
    {
        if ((pairlist.first.second & M_P1) == M_P1)
            piece = new Piece(NOIR, pairlist.first.first * 30, (pairlist.first.second ^ M_P1) * 30);
        else if ((pairlist.first.second & M_P2) == M_P2)
            piece = new Piece(BLANC, pairlist.first.first * 30, (pairlist.first.second ^ M_P2) * 30);
        PieceList.push_back(piece);

        if ((pairlist.second.second & M_P1) == M_P1)
        {
            piece2 = new Piece(NOIR, pairlist.second.first * 30, (pairlist.second.second ^ M_P1) * 30);
}
        else if ((pairlist.second.second & M_P2) == M_P2)
        {
            piece2 = new Piece(BLANC, pairlist.second.first * 30, (pairlist.second.second ^ M_P2) * 30);
    }
        PieceList.push_back(piece2);
    }
    return (PieceList);
}

void            Game::Play(QMouseEvent *event)
{
    std::pair<std::pair<int, int>, std::pair<int, int> >    pairlist;
    int         x;
    int         y;

    x = event->x();
    y = event->y();
    if (x % 30 != 0)
        x -= x % 30;
    if (y % 30 != 0)
        y -= y % 30;
    this->CheckRules();
    Piece *piece = new Piece(this->_Turn, x, y, this->_Goban->_Scene);
    if (this->_Game == true && this->_Referee->isMovePossible(this->_Map, piece) == true)
    {
        std::list<Piece*>    PieceList;
        PieceList.push_back(piece);
        this->ModifMap(ADD, PieceList);
        this->ChangeTurn();
        pairlist = this->_Referee->Toeat(this->_Map, (x / 30), (y / 30), piece->getTeam());
        PieceList = this->ToPieces(pairlist);
//        PieceList = this->_Referee->Toeat(this->_Map, piece);

        if (PieceList.size() != 0)
            this->ModifMap(DEL, PieceList);
        PieceList = this->_Referee->isEvent(this->_Map, piece, this->_ScoreB, this->_ScoreW);
        if (PieceList.size() == 1)
            this->EndGame(PieceList);
        if (PieceList.size() != 1 && this->_Gmode == 1)
            this->IaPlay(piece->getX() / 30, piece->getY() / 30);
    }
    else
    {
        delete (piece->getItem());
        delete (piece);
    }
}

void            Game::EndGame(std::list<Piece *> &PieceList)
{
    EndGameWin *EndGame = new EndGameWin(PieceList, this);

    EndGame->exec();
    this->_Game = false;
}

Score           *Game::getScore() const
{
    return (this->_Score);
}
