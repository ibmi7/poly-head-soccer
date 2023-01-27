/**
 * @file joueur.h
 * @brief The Joueur class
 * @version 1.0
 * @date 2023-01-27
 * @author Ibrahim Minthe & Youssef Skhiri
 * @version 1.0
*/


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
    /**
     * @brief Constructeur de la classe Joueur
     * @param solde
     * @param name
     * @param equipe
    */
    Joueur(int solde, std::string name, std::vector<std::string> equipe);
    /**
     * @brief Destructeur de la classe Joueur
    */
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
    std::string getActiveName() {return active_pers_name;};
    void setActiveName(std::string name) {active_pers_name = name;};
    static void reset();
    int buyPersonnage(std::string name);
    static void updateFile();
private:
    std::string active_pers_name;
    std::vector<std::string> equipe;
    std::vector<std::string> notOwned;
    int solde;
    std::string name;
};


std::ostream& operator<<(std::ostream& os, Joueur j);

#endif // JOUEUR_H
