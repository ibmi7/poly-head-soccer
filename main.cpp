#include <QApplication>
#include "game.h"
#include <sstream>
/*
 *Jeu Head Soccer

*/

Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // test de la classe Personnage
    std::cout << "Test de la classe Personnage" << std::endl;
    Personnage * france = new Personnage(Qt::Key_A,Qt::Key_W,Qt::Key_D,Qt::Key_S);
    assert(france->getLeft() == Qt::Key_A);
    assert(france->getUp() == Qt::Key_W);
    assert(france->getRight() == Qt::Key_D);
    assert(france->getDown() == Qt::Key_S);
    france->setInGame(1);
    assert(france->getInGame() == 1);
    france->setInGame(0);
    assert(france->getInGame() == 0);
    delete france;
    std::cout << "Test de la classe Personnage OK" << std::endl;
    // test de la classe Joueur
    std::cout << "Test de la classe Joueur" << std::endl;
    Joueur *j1 = new Joueur(1000, "j1", {"p1", "p2"});
    Joueur *j2 = new Joueur(1000, "j2", {"p3", "p4"});
    assert(j1->getEquipe().size() == 2);
    assert(j1->getSolde() == 1000);
    assert(j1->getName() == "j1");
    assert(j2->getEquipe().size() == 2);
    assert(j2->getSolde() == 1000);
    assert(j2->getName() == "j2");
    assert(Joueur::listeJoueur.size() == 2);
    delete j1;
    delete j2;
    assert(Joueur::listeJoueur.size() == 0);
    std::cout << "Test de la classe Joueur OK" << std::endl;


    game = new Game();
    //game->show();
    game->displayMainMenu();

    return a.exec();
}