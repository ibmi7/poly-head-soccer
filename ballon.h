/**
*@file ballon.h
*@brief The Ballon class
*@version 1.0
*@date 2023-01-27
*@author Ibrahim Minthe & Youssef Skhiri
*@version 1.0
**/


#ifndef BALLON_H
#define BALLON_H
#include <QObject>
#include <QMediaPlayer>
#include "cercle.h"

class Ballon: public Cercle
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur de la classe Ballon
    */
    Ballon();
    /**
     * @brief Destructeur de la classe Ballon
    */
    ~Ballon();
    /**
     * @brief Méthode qui permet de réinitialiser la position du ballon
    */
    void keyPressEvent(int key);
public slots:
    /**
     * @brief Méthode qui permet de déplacer le ballon
    */
    void move();
private:
    QMediaPlayer * _goal_sound;
    QMediaPlayer * _end_sound;
};

#endif // BALLON_H
