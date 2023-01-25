#ifndef FOCUSHANDLER_H
#define FOCUSHANDLER_H

#include <QObject>
#include "personnage.h"
#include <QGraphicsEllipseItem>

class FocusHandler : public QObject,public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    FocusHandler();
    void addPersonnage(Personnage * pers){liste.push_back(pers);};
    void keyPressEvent(QKeyEvent *event);
private:
    QVector<Personnage *> liste;
};

#endif // FOCUSHANDLER_H
