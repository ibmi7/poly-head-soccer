#ifndef JOUEUR_H
#define JOUEUR_H
#include <QObject>
#include <QMediaPlayer>
#include "personnage.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>


class Joueur
{
public:
    Joueur(int solde, std::string name, std::vector<std::string> equipe);
    //destructor
    ~Joueur();
    std::vector<std::string> getEquipe() {return equipe;};
    int getSolde() {return solde;};
    std::string getName() {return name;};
    void setSolde(int solde) {this->solde = solde;};
    void setEquipe(std::string equipe) {this->equipe.push_back(equipe);};    
    static std::vector<Joueur*> listeJoueur;
    static void clearListeJoueur();
    Personnage* active_pers;
    std::string getNom() {return (name);};
    std::vector<std::string> getNotOwned() {return notOwned;};
    int buyPersonnage(std::string name);
    static void updateFile();
private:
    std::vector<std::string> equipe;
    std::vector<std::string> notOwned;
    int solde;
    std::string name;
};


std::ostream& operator<<(std::ostream& os, Joueur j);

#endif // JOUEUR_H
