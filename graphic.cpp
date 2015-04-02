#include "graphic.h"
#include <QLabel>
Graphic::Graphic(int argc, char **argv)
{
    this->_Window = new QApplication(argc, argv);
}

Graphic::~Graphic()
{
    delete this->_Window;
}

int        Graphic::StartGraphic()
{
    Interface    a;

    a.show();
    return (this->_Window->exec());
}
