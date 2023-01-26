#include <QObject>
#include <QMediaPlayer>
#include "joueur.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <filesystem>

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

std::vector<Joueur*> Joueur::listeJoueur;

Joueur::Joueur(int solde, std::string name, std::vector<std::string> equipe)
{
    this->solde = solde;
    this->name = name;
    this->equipe = equipe;
    active_pers = nullptr;
    listeJoueur.push_back(this);
    for (auto pers : Personnage::getMap())
    {
        notOwned.push_back(pers.first);
        std::cout << pers.first << std::endl;
        for (auto pers2 : this->equipe)
        {
            std::cout << pers2 << std::endl;
            if (pers2.find(pers.first) != std::string::npos)
            {
                notOwned.pop_back();
                break;
            }
        }
    }
    std::cout << notOwned.size() << std::endl;
    for (auto pers : notOwned)
    {
        std::cout << pers << std::endl;
    } 
}

Joueur::~Joueur()
{
    listeJoueur.erase(std::remove(listeJoueur.begin(), listeJoueur.end(), this), listeJoueur.end());
}

void Joueur::updateFile()
{
    std::ofstream myfile ("joueurs.csv");
    if (myfile.is_open())
    {
        for (auto i : Joueur::listeJoueur)
        {
            myfile << i->getName() << " " << i->getSolde() << " ";
            for (auto j : i->getEquipe())
            {
                myfile << j << " ";
            }
            myfile << std::endl;
        }
        myfile.close();
    }
}

int Joueur::buyPersonnage(std::string name)
{
    if (Personnage::getPrice(name) <= solde)
    {
        solde -= Personnage::getPrice(name);
        equipe.push_back(name);
        for (auto pers : notOwned)
        {
            if (pers.find(name) != std::string::npos)
            {
                notOwned.erase(std::remove(notOwned.begin(), notOwned.end(), pers), notOwned.end());
                break;
            }
        }
        //mettre a jour le fichier
        Joueur::updateFile();
        return 1;
    }
    return 0;
}


std::ostream& operator<<(std::ostream& os, Joueur j)
{
    os << j.getName()<< std::endl;
    os << j.getSolde() << std::endl;
    os << j.getEquipe().size() << std::endl;
    int taille = j.getEquipe().size();
    for (int i = 0; i < j.getEquipe().size(); i++)
    {
        os << j.getEquipe()[i] << std::endl;
    }
    return os;
}


