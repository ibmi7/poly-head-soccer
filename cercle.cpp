#include "cercle.h"
#include <QTimer>
#include <QDebug>

int count = 0;

Cercle::Cercle(){
    //coordonnées
    vit.push_back(qMakePair(0,0));
    acc.push_back(qMakePair(0,0));
    radius = 25/2;
    mass = radius * 10.0f;
    //le connecter
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(10);
}

