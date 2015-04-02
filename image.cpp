#include    "image.h"

Image::Image(const std::string &str)
{
    this->_Image = new QLabel();
    this->_Image->setPixmap(QPixmap(str.c_str()));
}

Image::~Image()
{
    delete this->_Image;
}

QLabel  *Image::getImage() const
{
    return (this->_Image);
}
