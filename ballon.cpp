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
    _end_sound->setVolume(0);
    _end_sound->play();
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
/*     if (!scene()->collidingItems(this).isEmpty()){
        //count-=50;
        //if (count<0) count = 100;
        QGraphicsItem * item = scene()->collidingItems(this).last();
        //check if ground or another ball
        if (qgraphicsitem_cast<Ballon*>(item)){
            Ballon * ball = dynamic_cast<Ballon *>(item);
            // Distance between balls
            if (ball){
                double fDistance = sqrtf((x() - ball->x())*(x() - ball->x()) + (y() - ball->y())*(y() - ball->y()));
                // Normal
                double nx = (ball->x() - x()) / fDistance;
                double ny = (ball->y() - y()) / fDistance;

                // Tangent
                double tx = -ny;
                double ty = nx;

                // Dot Product Tangent
                double dpTan1 = vit[0].first * tx + vit[0].second * ty;
                double dpTan2 = ball->vit[0].first * tx + ball->vit[0].second * ty;

                // Dot Product Normal
                double dpNorm1 = vit[0].first * nx + vit[0].second * ny;
                double dpNorm2 = ball->vit[0].first * nx + ball->vit[0].second * ny;

                // Conservation of momentum in 1D
                double m1 = (dpNorm1 * (mass - ball->mass) + 2.0f * ball->mass * dpNorm2) / (mass + ball->mass);
                double m2 = (dpNorm2 * (ball->mass - mass) + 2.0f * mass * dpNorm1) / (mass + ball->mass);

                // Update ball velocities
                vit[0].first = tx * dpTan1 + nx * m1;
                vit[0].second = ty * dpTan1 + ny * m1;
                ball->vit[0].first = tx * dpTan2 + nx * m2;
                ball->vit[0].second = ty * dpTan2 + ny * m2;

                // Wikipedia Version - Maths is smarter but same
                //double kx = (b1->vx - b2->vx);
                //double ky = (b1->vy - b2->vy);
                //double p = 2.0 * (nx * kx + ny * ky) / (b1->mass + b2->mass);
                //b1->vx = b1->vx - p * b2->mass * nx;
                //b1->vy = b1->vy - p * b2->mass * ny;
                //b2->vx = b2->vx + p * b1->mass * nx;
                //b2->vy = b2->vy + p * b1->mass * ny;
            }
        }
    }
        //else : collision with the environment (lines)
    else{ */
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
        /*
        if (x()<= 0 || x()>= scene()->width()){
            // Update ball physics
            if (x()<= 0){
                setPos(0,y());
            }
            if (x()>= scene()->width()){
                setPos(scene()->width(),y());
            }
            vit[0].second *= -0.95;
            vit[0].first *= -0.95;
        }
        */

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
        //QTimer * timer = new QTimer();
        setPos(50,y());
       // timer->setInterval(10000);
        //timer->start();
        //if(timer->remainingTime()==0){
        //for(int i=0; i<200000000;i++){};
        //sleep(5);
        vit[0].first = 0;
        vit[0].second = 0;
        setPos(1500/2,0);
        game->score->increaseJ2();
        _goal_sound->setVolume(50);
        _goal_sound->play();
        //}
    }
    if (x()>= scene()->width()-240 && y()>=scene()->height()-400){
        //QTimer * timer = new QTimer();
        setPos(1500-150,y());
        //timer->setInterval(10000);
        //timer->start();
        //if(timer->remainingTime()==0){
        //for(int i=0; i<200000000;i++){};
        //sleep(5);
        vit[0].first = 0;
        vit[0].second = 0;
        setPos(1500/2,0);
        game->score->increaseJ1();
        _goal_sound->setVolume(50);
        _goal_sound->play();
        //}
    }



    // limite du sol
    /*
    if (y()> scene()->height()-200){
        setPos(x(),scene()->height()-200);
        vit[0].second *= -0.95;
        vit[0].first *= -0.95;
    }
    */
    //effet cage 2
    /*
    if(x()>= 1300){
        if(y()<scene()->height()-400){
                ;
                // Update ball physics
            vit[0].second *= -0.95;
            vit[0].first *= -0.95;



        }
    }
    // effet cage 1
    if(x()<=300){
        if(y()<scene()->height()-400){
                ;
                // Update ball physics
            vit[0].second *= -0.95;
            vit[0].first *= -0.95;



        }
    }
    if (y()< 0){
        setPos(x(),0);
    }
    */
    if(game->score->getScoreJ1() == 3 ){
        
        _end_sound->setVolume(50);
        _end_sound->play();
        game->replayMenu(0);
    }

    if(game->score->getScoreJ2() == 3 ){
        
        _end_sound->setVolume(50);
        _end_sound->play();
        game->replayMenu(1);
    }
}

