#ifndef SCORE_H
#define SCORE_H

#include <QtWidgets/QMainWindow>
#include <QtGui>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include "mylcd.h"
#include "image.h"
#include "define.h"

class Score : public QMainWindow
{
private:
    QHBoxLayout *_ScoreLayout;
    MyLCD       *_White;
    MyLCD       *_Black;
    Image       *_WhiteIcon;
    Image       *_BlackIcon;

public:
    Score(QWidget *parent = 0);
    ~Score();
    QHBoxLayout *getLayout() const;
    MyLCD       *getWhite() const;
    MyLCD       *getBlack() const;
};

#endif // SCORE_H
