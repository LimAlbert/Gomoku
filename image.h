#ifndef IMAGE_H
#define IMAGE_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <string>

class       Image : public QMainWindow
{
private:
    QLabel *_Image;
public:
    Image(const std::string &);
    QLabel  *getImage() const;
    ~Image();
};

#endif // IMAGE_H
