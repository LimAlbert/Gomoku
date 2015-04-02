#ifndef NEWGAMESLOT_H
#define NEWGAMESLOT_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QDialog>
#include <QtGui>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPushButton>

class NewGameSlot : public QDialog
{
    Q_OBJECT

    private:
        QHBoxLayout     *_RadiosLayout;
        QHBoxLayout     *_CheckLayout;
        QRadioButton    *_Jvj;
        QRadioButton    *_Jvia;
        QCheckBox       *_Cinq;
        QCheckBox       *_Double;
        QGroupBox       *_Radios;
        QGroupBox       *_Check;
        QVBoxLayout     *layout;
        QHBoxLayout     *boutons;
        QPushButton     *ok;
        QPushButton     *cancel;

    public:
        NewGameSlot(QWidget *parent = 0);
        void    CreateRadioLayout();
        void    CreateCheckLayout();
        void    CreateButtonsLayout();
        void    MergeLayouts();
        void    ConnectActions();
        int     getRules() const;
        int     getMode() const;
public slots:

};

#endif // NEWGAMESLOT_H
