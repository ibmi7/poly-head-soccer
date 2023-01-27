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
    /**
     * @brief displayMainMenu
     * @details Cette méthode permet d'afficher le menu principal. On y initialise également les joueurs et les personnages.
    **/
    void displayMainMenu();
    void close_game();
    /**
     * @brief selectPersonnageMenu
     * @details Cette méthode permet d'afficher le menu de sélection des personnages.
    **/
    void selectPersonnageMenu();
    /**
     * @brief marketMenu
     * @details Cette méthode permet d'afficher le menu du marché. 
    **/
    void marketMenu();
    /**
     * @brief buyPersonnage
     * @details Cette méthode permet d'acheter un personnage. 
    **/
    void buyPersonnage();
    /**
     * @brief setPersonnage
     * @details Cette méthode permet de définir le personnage choisi par le joueur. 
    **/
    void setPersonnage();
    /**
     * @brief play
     * @details Cette méthode permet de lancer la partie, en initialisant les personnages et le ballon, ainsi que le terrain.
    **/
    void play();
    void reset();

private:
};

#endif // GAME_H
