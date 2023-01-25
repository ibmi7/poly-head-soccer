#ifndef CERCLE_H
#define CERCLE_H
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QObject>

class Cercle: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Cercle();
    QVector<QPair<double,double>> getVit(){ return vit;};
    QVector<QPair<double,double>>& setVit(){ return vit;};
    double getMass() {return mass;};
    virtual void keyPressEvent(int key) = 0;
public slots:
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
