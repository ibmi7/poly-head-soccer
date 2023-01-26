#include "ballon.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include <cmath>
#include <QMediaPlayer>
#include "game.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

extern Game * game;
extern int count;
#define MAX_VX_BALL 15
#define MAX_VY_BALL 15

Ballon::Ballon() : Cercle(){
    vit.push_back(qMakePair(0,10));
    acc.push_back(qMakePair(0,10));
    setPixmap(QPixmap(":/Image/Image/Ball/ball1.png"));
    _goal_sound = new QMediaPlayer();
    _goal_sound->setMedia(QUrl("qrc:/Sounds/Sounds/but.wav"));
    _goal_sound->setVolume(0);
    _goal_sound->play();
    _end_sound = new QMediaPlayer();
    _end_sound->setMedia(QUrl("qrc:/Sounds/Sounds/coup_sifflet.mp3"));
    _end_sound->setVolume(50);
    _end_sound->play();
}

Ballon::~Ballon(){
    std::cout << "Ballon deleted" << std::endl;
    delete _goal_sound;
    delete _end_sound;
}

void Ballon::keyPressEvent(int key)
{
    if (key == Qt::Key_Space){
        vit[0].first = 0;
        vit[0].second = 0;
        setPos(1500/2,0);
    }
}

void Ballon::move()
{
    
    count++;
    double temps = count/100;
    if (temps>1) temps = 1;
    // Add Drag to emulate rolling friction
    acc[0].first = -vit[0].first * 0.0075;
    acc[0].second = -vit[0].second * 0.0075 + 0.10; //friction + poids

    // Update ball physics
    vit[0].first += acc[0].first*temps;
    if (vit[0].first>MAX_VX_BALL) vit[0].first = MAX_VX_BALL;
    if (vit[0].first<-MAX_VX_BALL) vit[0].first = -MAX_VX_BALL;
    vit[0].second += acc[0].second*temps;
    if (vit[0].second>MAX_VY_BALL) vit[0].second = MAX_VY_BALL;
    if (vit[0].second<-MAX_VY_BALL) vit[0].second = -MAX_VY_BALL;
    setPos(x()+vit[0].first*temps,y()+vit[0].second*temps);
        if (y()<= 0 || y()>= scene()->height()-200){
            // Update ball physics
            vit[0].second *= -0.98;
            if (y()> scene()->height()-200){
                setPos(x(),scene()->height()-200);
            }
            if (y()< 0){
                setPos(x(),0);
            }
        }

        if(x()>= scene()->width()-250 && y()<=scene()->height()-400){
            if(y()<scene()->height()-400){
                    ;
                    // Update ball physics
                vit[0].second *= 0.95;
                vit[0].first *= -0.95;
                }
        }
        // effet cage 1
        if(x()<=175 && y()<=scene()->height()-400){
            if(y()<scene()->height()-400){
                    ;
                    // Update ball physics
                vit[0].second *= 0.95;
                vit[0].first *= -0.95;
                }
        }

    //}
    //check if out of bounds


    if (x()<= 165 && y()>=scene()->height()-400){
        setPos(50,y());
        vit[0].first = 0;
        vit[0].second = 0;
        setPos(1500/2,0);
        game->score->increaseJ2();
        _goal_sound->setVolume(50);
        _goal_sound->play();
    }
    if (x()>= scene()->width()-240 && y()>=scene()->height()-400){
        setPos(1500-150,y());
        vit[0].first = 0;
        vit[0].second = 0;
        setPos(1500/2,0);
        game->score->increaseJ1();
        _goal_sound->setVolume(50);
        _goal_sound->play();
    }

    if(game->score->getScoreJ1() == 3 ){
        
        game->replayMenu(0);
    }

    if(game->score->getScoreJ2() == 3 ){
        
        game->replayMenu(1);
    }
}

