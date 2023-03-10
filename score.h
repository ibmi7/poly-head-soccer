/**
 * @file score.h
 * @brief The Score class
 * @version 1.0
 * @date 2023-01-27
 * @author Ibrahim Minthe & Youssef Skhiri
 * @version 1.0
 */
#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score : public QGraphicsTextItem
{
public:
    /**
     * @brief Constructeur de la classe Score
    */
    Score(QGraphicsItem *parent=0);
    void increaseJ1();
    void increaseJ2();
    int getScoreJ1();
    int getScoreJ2();

private:
    int _score_j1;
    int _score_j2;


};

#endif // SCORE_H
