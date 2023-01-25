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
    FocusHandler();
    void addPersonnage(Personnage * pers){liste.push_back(pers);};
    void setBallon(Ballon * ball){ballon = ball;};
    void keyPressEvent(QKeyEvent *event);
private:
    QVector<Personnage *> liste;
    Ballon * ballon;
};

#endif // FOCUSHANDLER_H
