#include "mylcd.h"

MyLCD::MyLCD(int value, int x, int y, QWidget *parent)
{
    this->lcd = new QLCDNumber(parent);
    lcd->setSegmentStyle(QLCDNumber::Flat);
    lcd->display(value);
    lcd->setFixedSize(x, y);
}
