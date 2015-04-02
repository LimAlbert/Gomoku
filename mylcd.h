#ifndef MYLCD_H
#define MYLCD_H

#include <QtGui>
#include <QtWidgets/QLCDNumber>

class MyLCD : public QWidget
{
public:
    MyLCD(int value, int x, int y, QWidget * parent = 0);
    QLCDNumber *lcd;
};

#endif // MYLCD_H
