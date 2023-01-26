#include "personnage.h"
#include "ballon.h"
#include <QDebug>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#define MAX_VX 7
#define MAX_VY 10
extern int count;

std::map<std::string, int> Personnage::_map;

void Personnage::keyPressEvent(int key){
    qDebug()<<key<<"\t"<<_left;
    if (key == _left){
        vit[0].first = -7;
    }
    else if (key == _right){
        vit[0].first = 7;
    }
    if (key == _up && y()== scene()->height()-250) vit[0].second =-10;
    if (key == _down){
        vit[0].first /=1.5;
        vit[0].second += 5;
    }
}




    void Personnage::move()
    {
        //check if out of bound

    if (inGame){
        float temps = count/100;
        if (temps>1) temps = 1;
        // Add Drag to emulate rolling friction
        //acc[0].first = -vit[0].first * 0.0075;
        if (y()>= scene()->height()) acc[0].second = -vit[0].second * 0.0075; //friction
        else acc[0].second = -vit[0].second * 0.0125 + 0.20; //friction + poids
        // Update ball physics
        //vit[0].first += acc[0].first*temps;
        if (vit[0].first>MAX_VX) vit[0].first = MAX_VX;
        if (vit[0].first<-MAX_VX) vit[0].first = -MAX_VX;
        vit[0].second += acc[0].second*temps;
        if (vit[0].second>MAX_VY) vit[0].second = MAX_VY;
        if (vit[0].second<-MAX_VY) vit[0].second = -MAX_VY;
        setPos(x()+vit[0].first*temps,y()+vit[0].second*temps);
        if (!scene()->collidingItems(this).isEmpty()){
            QGraphicsItem * item = scene()->collidingItems(this).first();
            //check if ground or another ball
            if (qgraphicsitem_cast<Ballon*>(item)){
                Ballon * ball = dynamic_cast<Ballon *>(item);
                // Distance between balls
                if (ball){
                    float fDistance = sqrtf((x() - ball->x())*(x() - ball->x()) + (y() - ball->y())*(y() - ball->y()));

                    // Normal
                    float nx = (ball->x() - x()) / fDistance;
                    float ny = (ball->y() - y()) / fDistance;

                    // Tangent
                    float tx = -ny;
                    float ty = nx;
                    // Dot Product Tangent
                    float dpTan2 = ball->getVit().at(0).first * tx + ball->getVit().at(0).second * ty;

                    // Dot Product Normal
                    float dpNorm1 = vit[0].first * nx + vit[0].second * ny;
                    float dpNorm2 = ball->getVit().at(0).first * nx + ball->getVit().at(0).second * ny;

                    // Conservation of momentum in 1D
                    float m2 = (dpNorm2 * (ball->getMass() - mass) + 2.0f * mass * dpNorm1) / (mass + ball->getMass());

                    // Update ball velocities
                    ball->setVit()[0].first = tx * dpTan2 + nx * m2*2;
                    ball->setVit()[0].second = ty * dpTan2 + ny * m2*2;

                }

            }
            else if (qgraphicsitem_cast<Personnage*>(item)){

                return;
            }
        }
            //else : collision with the environment (lines)
        else{
            if (y()<= 0 || y()>= scene()->height()){
                // Update ball physics
                if (y()> scene()->height()){
                    vit[0].second *= 0;
                    setPos(x(),scene()->height());
                }
                if (y()< 0){
                    vit[0].second *= -1;
                }
            }
            if (x()<= 0 || x()>= scene()->width()){
                // Update ball physics
                if (x()<= 0){
                    setPos(0,y());
                }
                if (x()>= scene()->width()){
                    setPos(scene()->width(),y());
                }

            }

        }
        //check if out of bounds - frontières
        if (y()> scene()->height()-250){
            setPos(x(),scene()->height()-250);
        }

        /*if (y()< 0){
            setPos(x(),0);
        }
        */
        if (x()<= 0){
            setPos(0,y());
        }
        if (x()>= scene()->width() - 150){
            setPos(scene()->width() - 150,y());
        }
    }
}

//operator <<
std::ostream& operator<<(std::ostream& os, Personnage& p)
{
    os << "Mouvement gauche : " << p.getLeft() << std::endl;
    os << "Mouvement droite : " << p.getRight() << std::endl;
    os << "Mouvement haut : " << p.getUp() << std::endl;
    os << "Mouvement bas : " << p.getDown() << std::endl;
    return os;
}
