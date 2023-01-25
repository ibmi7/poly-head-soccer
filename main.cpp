#include <QApplication>
#include "game.h"
/*
 *Jeu Head Soccer

*/

Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    //game->show();
    game->displayMainMenu();

    return a.exec();
}
/*
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include "personnage.h"
#include "ballon.h"
#include "focushandler.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //create a scene
    QGraphicsScene * scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1200,300);
    //createan item to put into the scene
    Personnage * pers = new Personnage(Qt::Key_Left,Qt::Key_Up,Qt::Key_Right,Qt::Key_Down);
    Personnage * pers2 = new Personnage(Qt::Key_Q,Qt::Key_Z,Qt::Key_D,Qt::Key_S);
    Ballon * ballon = new Ballon();
    FocusHandler * focus = new FocusHandler();
    ballon->setPos(scene->width()/2,-300);
    pers->setPixmap(QPixmap(":/Image/Player/Parts(more HD but not annimated)/P1.png"));
    pers2->setPixmap(QPixmap(":/Image/Player/Parts(more HD but not annimated)/p2.png"));
    pers->setPos(0,-300);
    pers2->setPos(scene->width(),-300);
    focus->setPos(-scene->width(),-scene->height());
    focus->addPersonnage(pers);
    focus->addPersonnage(pers2);
    //add the item to the scene
    scene->addItem(ballon);
    scene->addItem(pers);
    scene->addItem(pers2);
    scene->addItem(focus);
    // make personnage focusable
    focus->setFlag(QGraphicsItem::ItemIsFocusable);
    pers2->setFlag(QGraphicsItem::ItemIsFocusable);
    focus->setFocus();
    //add a view
    QGraphicsView * view = new QGraphicsView(scene);
    view->show();
    return a.exec();
}*/
