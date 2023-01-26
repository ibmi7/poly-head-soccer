#include <QObject>
#include <QMediaPlayer>
#include "joueur.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>

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
    std::cout<<"destruction joueur"<<std::endl;
    listeJoueur.erase(std::remove(listeJoueur.begin(), listeJoueur.end(), this), listeJoueur.end());
}

void Joueur::clearListeJoueur()
{
    for (auto i : listeJoueur)
    {
        delete i;
    }
    listeJoueur.clear();
}

void Joueur::updateFile()
{
    std::ofstream myfile;
    myfile.open("joueurs.csv",std::ofstream::out | std::ofstream::trunc);
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

void Joueur::reset()
{
    if (Joueur::listeJoueur.size() > 0)
    {
        for (auto i : listeJoueur)
        {
            delete i;
        }
    }
    assert(Joueur::listeJoueur.size() == 0);
    //init from default file
    std::string line;
    std::ifstream myfile;
    myfile.open("default.csv");
    if (myfile.is_open()){
        getline (myfile,line);
        std::vector<std::string> v;
        std::stringstream ss(line);
        std::string token;
        while(std::getline(ss, token, ' ')) {
            v.push_back(token);
        }
        std::vector<std::string> equipe;
        for(long unsigned int i = 2; i < v.size(); i++){
            equipe.push_back(v[i]);
        }
        new Joueur(std::stoi(v[1]),v[0],equipe);

        getline(myfile,line);
        std::vector<std::string> v2;
        std::stringstream ss2(line);
        std::string token2;
        while(std::getline(ss2, token2, ' ')) {
            v2.push_back(token2);
        }
        std::vector<std::string> equipe2;
        for(long unsigned int i = 2; i < v2.size(); i++){
            equipe2.push_back(v2[i]);
        }
        new Joueur(std::stoi(v2[1]),v2[0],equipe2);
    }
    myfile.close();
    Joueur::updateFile();
}

std::ostream& operator<<(std::ostream& os, Joueur j)
{
    os << j.getName()<< std::endl;
    os << j.getSolde() << std::endl;
    os << j.getEquipe().size() << std::endl;
    for (auto i : j.getEquipe())
    {
        os << i << std::endl;
    }
    return os;
}


