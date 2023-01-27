/**
 * @file focushandler.h
 * @brief The FocusHandler class
 * @version 1.0
 * @date 2023-01-27
 * @author Ibrahim Minthe & Youssef Skhiri
 * @version 1.0
 */


#ifndef FOCUSHANDLER_H
#define FOCUSHANDLER_H

#include <QObject>
#include "personnage.h"
#include "ballon.h"
#include <QGraphicsEllipseItem>

class FocusHandler : public QObject,public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur de la classe FocusHandler
    */
    FocusHandler();
    /**
     * @brief Destructeur de la classe FocusHandler
    */
    ~FocusHandler();
    /**
     * @brief Méthode qui permet d'ajouter un personnage à la liste
    */
    void addPersonnage(Personnage * pers){liste.push_back(pers);};
    /**
     * @brief Méthode qui de définir le ballon
    */
    void setBallon(Ballon * ball){ballon = ball;};
    /**
     * @brief Méthode qui permet de gérer les événements clavier
    */
    void keyPressEvent(QKeyEvent *event);
private:
    QVector<Personnage *> liste;
    Ballon * ballon;
};

#endif // FOCUSHANDLER_H
