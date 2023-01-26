#include "game.h"
#include "personnage.h"
#include "ballon.h"
#include "focushandler.h"
#include "button.h"
#include <QGraphicsTextItem>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QMessageBox>
#include <QtCore>
#include <cstdlib>
#include <iostream>
#include <QMediaPlayer>
#include "joueur.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>


QGraphicsView * view;



Game::Game(){
    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1500,768);
    setScene(scene);
    view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(1500,768);
    view->show();
}

void Game::close_game(){
    for (int i = 0; i < scene->items().size(); i++){
        scene->removeItem(scene->items()[i]);
    }
    delete scene;
    Joueur::clearListeJoueur();
    QApplication::quit();
}

void Game::displayMainMenu(){

    // create the title text
    scene->setBackgroundBrush(QImage(":/Image/Image/Environment/fond_ecran2.png"));
    QMediaPlayer * intro = new QMediaPlayer();
    intro->setMedia(QUrl("qrc:/Sounds/Sounds/intro.mp3"));
    intro->play();

    // create the play button
    Button* playButton = new Button(QString("Play"));
    int bxPos = scene->width()/2 -100 ;//playButton->boundingRect().width()/2;
    int byPos = 400;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(selectPersonnageMenu()));
    scene->addItem(playButton);

    // create the reset button
    Button* resetButton = new Button(QString("Reset"));
    int rxPos = scene->width()/2 -100;// resetButton->boundingRect().width()/2;
    int ryPos = 450;
    resetButton->setPos(rxPos,ryPos);
    connect(resetButton,SIGNAL(clicked()),this,SLOT(reset()));
    scene->addItem(resetButton);

    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = scene->width()/2 -100;// quitButton->boundingRect().width()/2;
    int qyPos = 500;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close_game()));
    scene->addItem(quitButton);

    //initialize the map of personnage
    std::string line2;
    std::ifstream myfile2 ("liste_players.csv");
    if (myfile2.is_open()){
        while ( getline (myfile2,line2) ){
            std::vector<std::string> v;
            std::stringstream ss(line2);
            std::string token;
            while(std::getline(ss, token, ' ')) {
                v.push_back(token);
            }
            Personnage::setMap()[v[0]] = std::stoi(v[1]);
        }
        myfile2.close();
    }
    else std::cout << "Unable to open file";
    for (auto const& x : Personnage::getMap())
    {
        std::cout << x.first  // string (key)
                  << ':'
                  << x.second   // string's value
                  << std::endl ;
    }
    //initialize the players
    std::string line;
    std::ifstream myfile ("joueurs.csv");
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
}

void Game::selectPersonnageMenu(){
    scene->clear();
    scene->setSceneRect(0,0,1500,768);
    QImage *bg = new QImage(":/Image/Image/Environment/back.png");
    bg->scaled(1500,768,Qt::KeepAspectRatio);
    scene->setBackgroundBrush(*bg);
    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Select your player"));
    QFont titleFont("comic sans",30);
    titleText->setFont(titleFont);
    //change color
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    titleText->setDefaultTextColor(Qt::white);
    int txPos = scene->width()/2 - 200;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);
    // add the personnage button
    int l = 0;
    int c = 0;
    int p = 0;
    for (auto i : Joueur::listeJoueur[0]->getEquipe()){
        Button* personnageButton = new Button(QString::fromStdString(i));
        personnageButton->setIndex(0);
        if (l%2 == 0){
            c = 0;
            p++;
        }
        else{
            c = 1;
        }
        int pxPos = scene->width()/2 - 600 + c*200;
        int pyPos = 400 + p*50;
        personnageButton->setPos(pxPos,pyPos);
        connect(personnageButton,SIGNAL(clicked()),this,SLOT(setPersonnage()));
        scene->addItem(personnageButton);
        l++;
    }
    l = 0;
    c = 0;
    p = 0;
    for (auto i : Joueur::listeJoueur[1]->getEquipe()){
        Button* personnageButton = new Button(QString::fromStdString(i));
        personnageButton->setIndex(1);
        if (l%2 == 0){
            c = 0;
            p++;
        }
        else{
            c = 1;
        }
        int pxPos = scene->width()/2 + 200 + c*200;
        int pyPos = 400 + p*50;
        personnageButton->setPos(pxPos,pyPos);
        connect(personnageButton,SIGNAL(clicked()),this,SLOT(setPersonnage()));
        scene->addItem(personnageButton);
        l++;
    }

    if (Joueur::listeJoueur[0]->active_pers!=nullptr){
        Joueur::listeJoueur[0]->active_pers = nullptr;
    }
    if (Joueur::listeJoueur[1]->active_pers!=nullptr){
     Joueur::listeJoueur[1]->active_pers = nullptr;
    }

    // create the play button
    Button* playButton = new Button(QString("Play"));
    int pxPos = scene->width()/2 -200;
    int pyPos = 700;
    playButton->setPos(pxPos,pyPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(play()));
    scene->addItem(playButton);

    // create the market button
    Button* marketButton = new Button(QString("Market"));
    int mxPos = scene->width()/2;
    int myPos = 700;
    marketButton->setPos(mxPos,myPos);
    connect(marketButton,SIGNAL(clicked()),this,SLOT(marketMenu()));
    scene->addItem(marketButton);
}

void Game::setPersonnage(){
    Button* buttonSender = qobject_cast<Button*>(sender()); 
    QGraphicsTextItem * name = buttonSender->getText();
    QString namePersonnage = name->toPlainText();
    std::string namePersonnageS = name->toPlainText().toStdString();
    if (buttonSender->getIndex() == 0){
        if (Joueur::listeJoueur[0]->active_pers!=nullptr){
            if (!Joueur::listeJoueur[0]->active_pers->pixmap().isNull()){
                scene->removeItem(Joueur::listeJoueur[0]->active_pers);
                Joueur::listeJoueur[0]->active_pers = nullptr;
            }
        }
        Joueur::listeJoueur[0]->active_pers = (new Personnage(Qt::Key_Left,Qt::Key_Up,Qt::Key_Right,Qt::Key_Down));
        QString path = ":/Image/Image/Player/p1_" + namePersonnage + ".png";
        Joueur::listeJoueur[0]->active_pers->setPixmap(QPixmap(path));
        Joueur::listeJoueur[0]->active_pers->setPos(scene->width()/2 - 150,300);
        scene->addItem(Joueur::listeJoueur[0]->active_pers);
    }
    else if (buttonSender->getIndex() == 1){
        if (Joueur::listeJoueur[1]->active_pers!=nullptr){
            if (!Joueur::listeJoueur[1]->active_pers->pixmap().isNull()){
                scene->removeItem(Joueur::listeJoueur[1]->active_pers);
                Joueur::listeJoueur[1]->active_pers = nullptr;
            }
        }
        Joueur::listeJoueur[1]->active_pers = (new Personnage(Qt::Key_Q,Qt::Key_Z,Qt::Key_D,Qt::Key_S));
        QString path = ":/Image/Image/Player/p2_" + namePersonnage + ".png";
        Joueur::listeJoueur[1]->active_pers->setPixmap(QPixmap(path));
        Joueur::listeJoueur[1]->active_pers->setPos(scene->width()/2 + 100,300);
        scene->addItem(Joueur::listeJoueur[1]->active_pers);
    }
}

void Game::marketMenu(){
    scene->clear();
    scene->setSceneRect(0,0,1500,768);
    QImage * bg = new QImage(":/Image/Image/Environment/fond_ecran3.png");
    *bg = bg->scaled(1500,768);
    scene->setBackgroundBrush(*bg);
    // add the title
    QGraphicsTextItem * titleText = new QGraphicsTextItem(QString("Market"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = scene->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 50;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);
    QGraphicsTextItem * messi = new QGraphicsTextItem(QString("Messi"));
    QFont messiFont("comic sans",30);
    messi->setFont(messiFont);
    int mxPos = scene->width()/4 - 100;
    int myPos = 100;
    messi->setPos(mxPos,myPos);
    scene->addItem(messi);
    //add remaining money
    QGraphicsTextItem * money = new QGraphicsTextItem(QString("Solde : ") + QString::number(Joueur::listeJoueur[0]->getSolde()));
    QFont moneyFont("comic sans",30);
    money->setFont(moneyFont);
    int moneyxPos = scene->width()/4 - 100;
    int moneyyPos = 150;
    money->setPos(moneyxPos,moneyyPos);
    scene->addItem(money);
    // add the name of the player and all the personnages not owned with their pictures and their price in a button
    int l = 0;
    for (auto i : Joueur::listeJoueur[0]->getNotOwned()){
        Button* personnageButton = new Button(QString::fromStdString(i));
        personnageButton->setIndex(0);
        int pxPos = 20+150*l;
        int pyPos = 300;
        personnageButton->setPos(pxPos,pyPos);
        connect(personnageButton,SIGNAL(clicked()),this,SLOT(buyPersonnage()));
        scene->addItem(personnageButton);
        //add the picture of the personnage
        QGraphicsPixmapItem * personnagePicture = new QGraphicsPixmapItem();
        QString path = ":/Image/Image/Player/p1_" + QString::fromStdString(i) + ".png";
        personnagePicture->setPixmap(QPixmap(path));
        personnagePicture->setPos(pxPos,pyPos-110);
        scene->addItem(personnagePicture);
        //add the price below the button
        QGraphicsTextItem * price = new QGraphicsTextItem(QString::fromStdString(std::to_string(Personnage::getPrice(i))) + "P");
        QFont priceFont("comic sans",15);
        price->setFont(priceFont);
        int priceXPos = pxPos;
        int priceYPos = pyPos + 50;
        price->setPos(priceXPos,priceYPos);
        scene->addItem(price);
        l++;
    }
    QGraphicsTextItem * ronaldo = new QGraphicsTextItem(QString("Ronaldo"));
    QFont ronaldoFont("comic sans",30);
    ronaldo->setFont(ronaldoFont);
    int rxPos = scene->width()/4 - 100;
    int ryPos = 450;
    ronaldo->setPos(rxPos,ryPos);
    scene->addItem(ronaldo);
    //add remaining money
    QGraphicsTextItem * money2 = new QGraphicsTextItem(QString("Solde : ") + QString::number(Joueur::listeJoueur[1]->getSolde()));
    QFont moneyFont2("comic sans",30);
    money2->setFont(moneyFont2);
    int moneyxPos2 = scene->width()/4 - 100;
    int moneyyPos2 = 500;
    money2->setPos(moneyxPos2,moneyyPos2);
    scene->addItem(money2);
    // add the name of the player and all the personnages not owned with their pictures and their price in a button
    l = 0;
    for (auto i : Joueur::listeJoueur[1]->getNotOwned()){
        Button* personnageButton = new Button(QString::fromStdString(i));
        personnageButton->setIndex(1);
        int pxPos = 20+150*l;
        int pyPos = 650;
        personnageButton->setPos(pxPos,pyPos);
        connect(personnageButton,SIGNAL(clicked()),this,SLOT(buyPersonnage()));
        scene->addItem(personnageButton);
        //add the picture of the personnage
        QGraphicsPixmapItem * personnagePicture = new QGraphicsPixmapItem();
        QString path = ":/Image/Image/Player/p2_" + QString::fromStdString(i) + ".png";
        personnagePicture->setPixmap(QPixmap(path));
        personnagePicture->setPos(pxPos,pyPos-110);
        scene->addItem(personnagePicture);
        //add the price below the button
        QGraphicsTextItem * price = new QGraphicsTextItem(QString::fromStdString(std::to_string(Personnage::getPrice(i))) + "P");
        QFont priceFont("comic sans",15);
        price->setFont(priceFont);
        int priceXPos = pxPos;
        int priceYPos = pyPos + 50;
        price->setPos(priceXPos,priceYPos);
        scene->addItem(price);
        l++;
    }
    // add the back button on the right
    Button * backButton = new Button(QString("Back"));
    int bxPos = scene->width() - 200;
    int byPos = scene->height()/2+75;
    backButton->setPos(bxPos,byPos);
    connect(backButton,SIGNAL(clicked()),this,SLOT(selectPersonnageMenu()));
    scene->addItem(backButton);

}

void Game::buyPersonnage(){
    Button * button = qobject_cast<Button *>(sender());
    int index = button->getIndex();
    std::string name = button->get_text();
    int b = Joueur::listeJoueur[index]->buyPersonnage(name);
    if (!b){
        QMessageBox::information(this,"Information","You don't have enough money to buy this personnage");
    }
    else{
        QMessageBox::information(this,"Information","You have successfully bought this personnage");
    }
    marketMenu();
}

void Game::play(){
    scene->clear();
    scene->setSceneRect(0,0,1500,768);
    QImage * bg = new QImage(":/Image/Image/Environment/terrain_foot8.png");
    *bg = bg->scaled(1500,768);
    scene->setBackgroundBrush(*bg);
    // create the personnage
    Personnage * p1 = new Personnage(Qt::Key_Left,Qt::Key_Up,Qt::Key_Right,Qt::Key_Down);
    Personnage * p2 = new Personnage(Qt::Key_Q,Qt::Key_Z,Qt::Key_D,Qt::Key_S);
    p1->setInGame(true);
    p1->setPixmap(QPixmap(":/Image/Image/Player/p1_" + QString::fromStdString(Joueur::listeJoueur[0]->getEquipe()[0]) + ".png"));
    p2->setInGame(true);
    p2->setPixmap(QPixmap(":/Image/Image/Player/p2_" + QString::fromStdString(Joueur::listeJoueur[1]->getEquipe()[0]) + ".png"));
    if (Joueur::listeJoueur[0]->active_pers != nullptr){
        qDebug() << "p1";
        qDebug() << QString::fromStdString(Joueur::listeJoueur[0]->getEquipe()[0]);
        if (!Joueur::listeJoueur[0]->active_pers->pixmap().isNull()) p1->setPixmap(Joueur::listeJoueur[0]->active_pers->pixmap());
    }
    if (Joueur::listeJoueur[1]->active_pers != nullptr){
        qDebug() << "p2";
        if (!Joueur::listeJoueur[1]->active_pers->pixmap().isNull()) p2->setPixmap(Joueur::listeJoueur[1]->active_pers->pixmap());
    } 
    p1->setPos(0,scene->height()-200);
    p2->setPos(scene->width()-50,scene->height()-200);
    Ballon * ballon = new Ballon();
    FocusHandler * focus = new FocusHandler();
    QGraphicsPixmapItem * cage1 = new QGraphicsPixmapItem();
    QGraphicsPixmapItem * cage2 = new QGraphicsPixmapItem();
    QPixmap * cage1_scaled = new QPixmap(":/Image/Image/Environment/filet_ness2_ns.png");
    cage1_scaled->scaled(50,100);
    ballon->setPos(scene->width()/2,-scene->height());
    cage1->setPixmap(*cage1_scaled);
    cage2->setPixmap(QPixmap(":/Image/Image/Environment/filet_ness_ns.png"));
    focus->setPos(-scene->width(),-scene->height());
    cage1->setPos(50,scene->height()/2);
    cage2->setPos(scene->width()-200,scene->height()/2);
    scene->addItem(ballon);
    scene->addItem(cage1);
    scene->addItem(cage2);
    scene->addItem(focus);
    scene->addItem(p1);
    scene->addItem(p2);
    focus->addPersonnage(p1);
    focus->addPersonnage(p2);
    focus->setBallon(ballon);
    focus->setFlag(QGraphicsItem::ItemIsFocusable);
    focus->setFocus();
    score = new Score();
    scene->addItem(score);
    view->show();
}

void Game::replayMenu(int i){
    std::cout << "je suis  dans replayMenu" << std::endl;
    Joueur::listeJoueur[0]->active_pers = nullptr;
    Joueur::listeJoueur[1]->active_pers = nullptr;
    //delete all items from the scene
    scene->clear();
    scene->setSceneRect(0,0,1500,768);
    // update solde and file
    Joueur::listeJoueur[i]->setSolde(Joueur::listeJoueur[i]->getSolde()+100);
    Joueur::updateFile();
    // create the replay button
    Button* replayButton = new Button(QString("Replay"));
    int bxPos = this->width()/2 - replayButton->boundingRect().width()/2;
    int byPos = 275;
    replayButton->setPos(bxPos,byPos);
    connect(replayButton,SIGNAL(clicked()),this,SLOT(selectPersonnageMenu()));
    scene->addItem(replayButton);
    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close_game()));
    scene->addItem(quitButton);
}

void Game::reset(){
    Joueur::reset();
}