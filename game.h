/**
 * @file game.h
 * @brief The Game class
 * @version 1.0
 * @date 2023-01-27
 * @author Ibrahim Minthe & Youssef Skhiri
 * @version 1.0
*/


#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "personnage.h"
#include "ballon.h"
#include "focushandler.h"
#include "score.h"
#include "joueur.h"
#include <string>
#include <vector>
#include <QComboBox>
#include <QPushButton>
#include <QMenu>
class Game: public QGraphicsView{
    Q_OBJECT
public:
    /**
     * @brief Constructeur de la classe Game
    */
    Game(QWidget* parent=NULL);

    void replayMenu(int i);
    bool comparaison(std::string name,std::vector<std::string> equipe);
    void new_CSV(std::vector <Joueur> j);

    //QString getWhosTurn();
    //void setWhosTurn(QString player);

    // public attributes
    QGraphicsScene* scene;
    Ballon* ballon;
    Personnage* personnage;
    FocusHandler* f;
    Score * score;

public slots:
    void displayMainMenu();
    void close_game();
    void selectPersonnageMenu();
    void marketMenu();
    void buyPersonnage();
    void setPersonnage();
    void play();
    void reset();

private:
};

#endif // GAME_H
