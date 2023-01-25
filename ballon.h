#ifndef BALLON_H
#define BALLON_H
#include <QObject>
#include <QMediaPlayer>
#include "cercle.h"

class Ballon: public Cercle
{
    Q_OBJECT
public:
    Ballon();
    /*
    Ballon() : Cercle(){
        vit.push_back(qMakePair(0,10));
        acc.push_back(qMakePair(0,10));
        setPixmap(QPixmap(":/Image/Image/Ball/ball1.png"));
        _goal_sound = new QMediaPlayer();
        _goal_sound->setMedia(QUrl("qrc:/Sounds/Sounds/but.wav"));
        _end_sound = new QMediaPlayer();
        _end_sound->setMedia(QUrl("qrc:/Sounds/Sounds/coup_sifflet.mp3"));
    };
    */
public slots:
    void move();
private:
    //long id;
    QMediaPlayer * _goal_sound;
    QMediaPlayer * _end_sound;
};

#endif // BALLON_H
