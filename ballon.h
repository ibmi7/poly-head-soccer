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
    ~Ballon();
    void keyPressEvent(int key);
public slots:
    void move();
private:
    //long id;
    QMediaPlayer * _goal_sound;
    QMediaPlayer * _end_sound;
};

#endif // BALLON_H
