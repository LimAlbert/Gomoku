#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QApplication>
#include <string>
#include "interface.h"

class       Graphic
{
private:
    QApplication *_Window;

public:
    Graphic(int, char **);
    ~Graphic();
    int         StartGraphic();
};

#endif // GRAPHIC_H
