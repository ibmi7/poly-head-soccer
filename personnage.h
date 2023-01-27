/**
 * @file personnage.h
 * @brief The Personnage class
 * @version 1.0
 * @date 2023-01-27
 * @author Ibrahim Minthe & Youssef Skhiri
 * @version 1.0
*/


#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include "cercle.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <string>

class Personnage : public Cercle
{
public:
    /**
     * @brief Constructeur de la classe Personnage
     * @param left : touche de déplacement vers la gauche
     * @param up : touche de déplacement vers le haut
     * @param right : touche de déplacement vers la droite
     * @param down : touche de déplacement vers le bas
    */
    Personnage(int left,int up,int right,int down) : Cercle(){
        _up = up;
        _left = left;
        _right = right;
        _down = down;
        radius = 30/2;
        mass = radius * 10.0f;
        _name = "";
    };
    /**
     * @brief keyPressEvent
     * @param key
     * @details Cette méthode permet de détecter la touche appuyée
    */
    void keyPressEvent(int key);
    int getLeft() {return _left;};
    int getUp() {return _up;};
    int getRight() {return _right;};
    int getDown() {return _down;};
    void setInGame(int i) {inGame = i;};
    int getInGame() {return inGame;};
    static std::map<std::string, int> getMap() {return _map;};
    static std::map<std::string, int> &setMap() {return _map;};
    static void clearMap() {_map.clear();};
    static int getPrice(std::string name) {return _map[name];};

public slots:
    /**
     * @brief move
     * @details Cette méthode permet de déplacer le personnage
    */
    void move();
private:
    int _left;
    int _right;
    int _up;
    int _down;
    std::string _name;
    /**
     * @brief _map
     * @details Cette map permet de stocker le prix de chaque personnage
    */
    static std::map<std::string, int> _map;
    int inGame = 0;

};

//operator<<
std::ostream& operator<<(std::ostream& os, Personnage p);

#endif // PERSONNAGE_H
