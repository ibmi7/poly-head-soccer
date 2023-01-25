#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include "cercle.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <string>

class Personnage : public Cercle
{
public:
    Personnage(int left,int up,int right,int down) : Cercle(){
        _up = up;
        _left = left;
        _right = right;
        _down = down;
        radius = 30/2;
        mass = radius * 10.0f;
        _name = "";
    };
    void keyPressEvent(int key);
    int getLeft() {return _left;};
    int getUp() {return _up;};
    int getRight() {return _right;};
    int getDown() {return _down;};
    static std::map<std::string, int> getMap() {return _map;};
    static std::map<std::string, int> &setMap() {return _map;};
    static int getPrice(std::string name) {return _map[name];};

public slots:
    void move();
private:
    int _left;
    int _right;
    int _up;
    int _down;
    std::string _name;
    static std::map<std::string, int> _map;

};

#endif // PERSONNAGE_H
