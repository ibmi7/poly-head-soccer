#include "score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    // Initialization of the scores
    _score_j1 = 0;
    _score_j2 = 0;

    // Draw the score

    setPlainText(QString("Score J1 : ") + QString::number(_score_j1) + QString("\n") + QString("Score J2 : ") + QString::number(_score_j2));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times",16));
}


void Score::increaseJ1(){
    _score_j1++;
    setPlainText(QString("Score J1 : ") + QString::number(_score_j1) + QString("\n") + QString("Score J2 : ") + QString::number(_score_j2));
}

void Score::increaseJ2(){
    _score_j2++;
    setPlainText(QString("Score J1 : ") + QString::number(_score_j1) + QString("\n") + QString("Score J2 : ") + QString::number(_score_j2));
}

int Score::getScoreJ1(){
    return _score_j1;
}

int Score::getScoreJ2(){
    return _score_j2;
}
