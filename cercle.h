/**
 * @file cercle.h
 * @brief The Cercle class
 * @version 1.0
 * @date 2023-01-27
 * @author Ibrahim Minthe & Youssef Skhiri
 * @version 1.0
*/


#ifndef CERCLE_H
#define CERCLE_H
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QObject>

class Cercle: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur de la classe Cercle
    */
    Cercle();
    QVector<QPair<double,double>> getVit(){ return vit;};
    QVector<QPair<double,double>>& setVit(){ return vit;};
    double getMass() {return mass;};
    /**
     * @brief keyPressEvent
     * @param key
     * @details Cette méthode permet de détecter la touche appuyée
     * @details Cette méthode est virtuelle pure
    */
    virtual void keyPressEvent(int key) = 0;
public slots:
    /**
     * @brief move
     * @details Cette méthode permet de déplacer le cercle
     * @details Cette méthode est virtuelle pure
    */
    virtual void move()=0;
protected:
    QVector<QPair<double,double>> vit;
    QVector<QPair<double,double>> acc;
    double radius;
    double mass;
private:
    long id;
};

#endif // CERCLE_H
