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
    // constructors
    Game(QWidget* parent=NULL);

    // public methods
    void displayMainMenu();
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
    //void start();
    void close_game();
/*     void selectplayerMenu();
    void selectcompteMenu(); */
    void selectPersonnageMenu();
    void marketMenu();
    void buyPersonnage();
    void setPersonnage();
    void play();
/*     void buyMenu();
    void choose_picture(int i);
    void select_joueur(int i);
    void player_select(int i);
    void buy_for_j1();
    void buy_for_j2(); */

private:
    // private methods
    //void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    //void drawGUI();
    //void createNewCard(QString player);
    //void createInitialCards();
    //void drawCards();

    // private attributes
    //QString whosTurn_;
    //QGraphicsTextItem* whosTurnText;
    //QList<Hex* > player1Cards;
    //QList<Hex* > player2Cards;
};

#endif // GAME_H
