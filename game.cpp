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



Game::Game(QWidget *parent){
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
    /*
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Head Soccer"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = scene->width()/2 - 200;//titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);
    */
    // create the play button
    Button* playButton = new Button(QString("Play"));
    int bxPos = scene->width()/2 -100 ;//playButton->boundingRect().width()/2;
    int byPos = 400;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(selectPersonnageMenu()));
    scene->addItem(playButton);

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
        for(int i = 2; i < v.size(); i++){
            equipe.push_back(v[i]);
        }
        Joueur * messi = new Joueur(std::stoi(v[1]),v[0],equipe);

        getline(myfile,line);
        std::vector<std::string> v2;
        std::stringstream ss2(line);
        std::string token2;
        while(std::getline(ss2, token2, ' ')) {
            v2.push_back(token2);
        }
        std::vector<std::string> equipe2;
        for(int i = 2; i < v2.size(); i++){
            equipe2.push_back(v2[i]);
        }
        Joueur * ronaldo = new Joueur(std::stoi(v2[1]),v2[0],equipe2);
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
    //unfocus player

    // add the players choice
/*     QGraphicsTextItem * messi = new QGraphicsTextItem(QString("Messi"));
    QFont messiFont("comic sans",30);
    messi->setFont(messiFont);
    messi->setDefaultTextColor(Qt::white);
    int mxPos = scene->width()/2 - 300;
    int myPos = 200;
    messi->setPos(mxPos,myPos);
    scene->addItem(messi);

    QGraphicsTextItem * ronaldo = new QGraphicsTextItem(QString("Ronaldo"));
    QFont ronaldoFont("comic sans",30);
    ronaldo->setFont(ronaldoFont);
    ronaldo->setDefaultTextColor(Qt::white);
    int rxPos = scene->width()/2; + 100;
    int ryPos = 200;
    ronaldo->setPos(rxPos,ryPos);
    scene->addItem(ronaldo); */
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
/*         int pxPos = scene->width()/2 - 300;
        int pyPos = 300 + l*50; */
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
    int pxPos = scene->width()/2 -200;// quitButton->boundingRect().width()/2;
    int pyPos = 700;
    playButton->setPos(pxPos,pyPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(play()));
    scene->addItem(playButton);

    // create the market button
    Button* marketButton = new Button(QString("Market"));
    int mxPos = scene->width()/2;// quitButton->boundingRect().width()/2;
    int myPos = 700;
    marketButton->setPos(mxPos,myPos);
    connect(marketButton,SIGNAL(clicked()),this,SLOT(marketMenu()));
    scene->addItem(marketButton);
}

void Game::setPersonnage(){
    Button* buttonSender = qobject_cast<Button*>(sender()); // retrieve the button you have clicked
    QGraphicsTextItem * name = buttonSender->getText();
    //graphicsTextItem to QString
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
        int pxPos = 20+175*l;
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
        int pxPos = 20+175*l;
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
    int bxPos = scene->width() - 150;
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
        p1->setPixmap(Joueur::listeJoueur[0]->active_pers->pixmap());
    }
    if (Joueur::listeJoueur[1]->active_pers != nullptr){
        qDebug() << "p2";
        p2->setPixmap(Joueur::listeJoueur[1]->active_pers->pixmap());
    } 
    p1->setPos(0,scene->height()-200);
    p2->setPos(scene->width()-50,scene->height()-200);
    Ballon * ballon = new Ballon();
    FocusHandler * focus = new FocusHandler();
    QGraphicsPixmapItem * cage1 = new QGraphicsPixmapItem();
    QGraphicsPixmapItem * cage2 = new QGraphicsPixmapItem();
    QPixmap * cage1_scaled = new QPixmap(":/Image/Image/Environment/filet_ness2_ns.png");
    QPixmap * cage2_scaled = new QPixmap(":/Image/Image/Environment/goal_1.png");
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
    scene->clear();
    scene->setSceneRect(0,0,1500,768);
    // update solde and file
    Joueur::listeJoueur[i]->setSolde(Joueur::listeJoueur[i]->getSolde()+100);
    Joueur::updateFile();
    /* if(i==1){
        if(indice_j1 == 0) {
            joueurs[0].setSolde(joueurs[0].getSolde() + 100);
            joueurs_j1 = joueurs[0].getEquipe();
            new_CSV(joueurs);
        }
        if(indice_j1 == 1) {
            joueurs[1].setSolde(joueurs[1].getSolde() + 100);
            std::cout << "joueurs modifié dans replayMenu" << std::endl;
            for(auto i : joueurs) std::cout << i << std::endl;
            joueurs_j1 = joueurs[1].getEquipe();
            std::cout << "jouers_j1 avec solde modifié" << std::endl;
            for(const auto&i : joueurs_j1) std::cout << i << std::endl;
            new_CSV(joueurs);
        }
        if(indice_j1 == 2) {
            joueurs[2].setSolde(joueurs[2].getSolde() + 100);
            joueurs_j1 = joueurs[2].getEquipe();
            new_CSV(joueurs);
        }
    }
    if(i==2){
        if(indice_j2 == 0) {
            joueurs[0].setSolde(joueurs[0].getSolde() + 100);
            std::cout << "joueurs modifié dans replayMenu" << std::endl;
            for(auto i : joueurs) std::cout << i << std::endl;
            joueurs_j2 = joueurs[0].getEquipe();
            std::cout << "jouers_j2 avec solde modifié" << std::endl;
            for(const auto&i : joueurs_j2) std::cout << i << std::endl;
            new_CSV(joueurs);
        }
        if(indice_j2 == 1) {
            joueurs[1].setSolde(joueurs[1].getSolde() + 100);
            joueurs_j2 = joueurs[1].getEquipe();
            new_CSV(joueurs);
        }
        if(indice_j2 == 2) {
            joueurs[2].setSolde(joueurs[2].getSolde() + 100);
            joueurs_j2 = joueurs[2].getEquipe();
            new_CSV(joueurs);
        }

    }
 */
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

/* 
void Game::selectplayerMenu(){
    scene->clear();
    scene->setBackgroundBrush(QImage(":/Image/Image/Environment/fond_ecran3.png"));

    
    if(indice_j1 == 0) joueurs_j1 = joueurs[0].getEquipe();
    if(indice_j1 == 1) joueurs_j1 = joueurs[1].getEquipe();
    if(indice_j1 == 2) joueurs_j1 = joueurs[2].getEquipe();

    if(indice_j2 == 0) joueurs_j2 = joueurs[0].getEquipe();
    if(indice_j2 == 1) joueurs_j2 = joueurs[1].getEquipe();
    if(indice_j2 == 2) joueurs_j2 = joueurs[2].getEquipe();
    
    for(auto i : joueurs_j1) std::cout << i << std::endl;
    for(auto i : joueurs_j2) std::cout << i << std::endl;

    QGraphicsPixmapItem * french_player = new QGraphicsPixmapItem();
    french_player->setPixmap(QPixmap(":/Image/Image/Player/p1_blue.png"));
    french_player->setPos(scene->width()/2 +40 ,100);
    QGraphicsPixmapItem * guinean_player = new QGraphicsPixmapItem();
    guinean_player->setPixmap(QPixmap(":/Image/Image/Player/p1_black3.png"));
    guinean_player->setPos(scene->width()/2 +40  ,250);
    QGraphicsPixmapItem * mexican_player = new QGraphicsPixmapItem();
    mexican_player->setPixmap(QPixmap(":/Image/Image/Player/p1_mex.png"));
    mexican_player->setPos(scene->width()/2 +40  ,410);
    QGraphicsPixmapItem * american_player = new QGraphicsPixmapItem();
    american_player->setPixmap(QPixmap(":/Image/Image/Player/p1_blond.png"));
    american_player->setPos(scene->width()/2  +40,570);
    scene->addItem(french_player);
    scene->addItem(guinean_player);
    scene->addItem(mexican_player);
    scene->addItem(american_player);

    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Select your player"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = scene->width()/2 - 200;//- titleText->boundingRect().width()/2;
    int tyPos = 0;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    Button* playButton = new Button(QString("Start"));
    int bxPos = scene->width()/2 +200 ;//- playButton->boundingRect().width()/2;
    int byPos = 700;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);
    int k =0;
    for(auto i : joueurs_dispo){
            const char* name_p1 = i.name.c_str();
            Button* player_j1 = new Button(QString(name_p1));
            int fxPos = scene->width()/2 -400;//- franceplayer_j1->boundingRect().width()/2;
            int fyPos = 150 +155*k;
            std::cout<<"fyPos vaut : "<<fxPos<<std::endl;
            player_j1->setPos(fxPos,fyPos);
            QSignalMapper* signalMapper = new QSignalMapper(this);
            connect(player_j1, SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper->setMapping(player_j1, p);
            connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(choose_picture(int))); 
            scene->addItem(player_j1);
            p++;

            const char* name_p2 = i.name.c_str();
            Button* player_j2 = new Button(QString(name_p2));
            int nxPos = scene->width()/2 +400;//- franceplayer_j1->boundingRect().width()/2;
            int nyPos = 150 + 155*k;
            std::cout<<"nyPos vaut : "<<nyPos<<std::endl;
            player_j2->setPos(nxPos,nyPos);
            QSignalMapper* signalMapper2 = new QSignalMapper(this);
            connect(player_j2, SIGNAL(clicked()), signalMapper2, SLOT(map()));
            signalMapper2->setMapping(player_j2, p);
            connect(signalMapper2, SIGNAL(mapped(int)), this, SLOT(choose_picture(int))); 
            scene->addItem(player_j2);
            p++;
            k++;
            std::cout<<"k vaut : "<<k<<std::endl;
            std::cout<<"p vaut : "<<p<<std::endl;
    }
    p=0;
    k=0;

    Button* achatButton = new Button(QString("Acheter"));
    int oxPos = scene->width()/2 -200 ;//- playButton->boundingRect().width()/2;
    int pyPos = 700;
    achatButton->setPos(oxPos,pyPos);
    connect(achatButton,SIGNAL(clicked()),this,SLOT(buyMenu()));
    scene->addItem(achatButton);
    
}

void Game::choose_picture(int i){
    std::cout<<"i vaut : "<<i<<std::endl;
    if(i == 0){
        std::cout<< "je suis passe par choose_picture";
        std::string name = "france";
        if(comparaison(name,joueurs_j1)==true) choix_j1 = 0;
        else{
            QMessageBox::information(this,"Erreur","Vous ne possedez pas ce joueur");
            choix_j1 = -1;
        }
    }
    else if(i == 1){
        std::cout<< "je suis passe par choose_picture";
        std::string name = "france";
        if(comparaison(name,joueurs_j2)==true) choix_j2 = 0;
        else{
            QMessageBox::information(this,"Erreur","Vous ne possedez pas ce joueur");
            choix_j2 = -1;
        }
    }
    else if(i == 2){
        std::cout<< "je suis passe par choose_picture";
        std::string name = "guinee";
        if(comparaison(name,joueurs_j1)==true) choix_j1 = 1;
        else{
            QMessageBox::information(this,"Erreur","Vous ne possedez pas ce joueur");
            choix_j1 = -1;
        }
    }
    else if(i == 3){
        std::cout<< "je suis passe par choose_picture";
        std::string name = "guinee";
        if(comparaison(name,joueurs_j2)==true) choix_j2 = 1;
        else{
            QMessageBox::information(this,"Erreur","Vous ne possedez pas ce joueur");
            choix_j2 = -1;
        }
    }
    else if(i == 4){
        std::cout<< "je suis passe par choose_picture";
        std::string name = "mexique";
        if(comparaison(name,joueurs_j1)==true) choix_j1 = 2;
        else{
            QMessageBox::information(this,"Erreur","Vous ne possedez pas ce joueur");
            choix_j1 = -1;
        }
    }
    else if(i == 5){
        std::cout<< "je suis passe par choose_picture";
        std::string name = "mexique";
        if(comparaison(name,joueurs_j2)==true) choix_j2 = 2;
        else{
            QMessageBox::information(this,"Erreur","Vous ne possedez pas ce joueur");
            choix_j2 = -1;
        }
    }
    else if(i==6){
        std::cout<< "je suis passe par choose_picture";
        std::string name = "american";
        if(comparaison(name,joueurs_j1)==true) choix_j1 = 3;
        else{
            QMessageBox::information(this,"Erreur","Vous ne possedez pas ce joueur");
            choix_j1 = -1;
        }
    }
    else if(i == 7){
        std::cout<< "je suis passe par choose_picture";
        std::string name = "american";
        if(comparaison(name,joueurs_j2)==true) choix_j2 = 3;
        else{
            QMessageBox::information(this,"Erreur","Vous ne possedez pas ce joueur");
            choix_j2 = -1;
        }
    }
}



void Game::selectcompteMenu(){
    joueurs.clear();
    std::cout<<"je suis passe par selectcompteMenu"<<std::endl;
    for(auto i : joueurs) std::cout << i << std::endl;
    scene->clear();
    scene->setSceneRect(0,0,1500,768);
    
    j=0;
    int nb_joueur = 0;
    std::string line;
    std::string column;
    std::ifstream myfile ("sauvegarde2.csv");
    while(getline(myfile,line)){
        std::stringstream ss(line);
        getline(ss,column,';');
        std::string name = column;
        getline(ss,column,';');
        int solde = std::stoi(column);
        std::vector<std::string> equipe;
        while(getline(ss,column,';')){
            equipe.push_back(column);
            //std::cout << column << std::endl;
        }
        Joueur m = Joueur(solde,name,equipe);
        joueurs.push_back(m);
        nb_joueur++;
    }
    line.clear();
    column.clear();
    for(auto i : joueurs) std::cout << i << std::endl;
    
    for(int i = 0; i < nb_joueur; i++){
        
        //std::cout<<"i vaut : "<<i<<std::endl;
        //std::cout<<"j vaut : "<<j<<std::endl;
        const char* name = joueurs[i].getName().c_str();
        Button* joueur = new Button(QString(name));
        int aPos = scene->width()/2 - 400;//- franceplayer_j1->boundingRect().width()/2;
        int bPos = 250 + i*200;
        joueur->setPos(aPos,bPos);
        QSignalMapper* signalMapper = new QSignalMapper(this);
        connect(joueur, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(joueur, j);
        connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(select_joueur(int))); 
        scene->addItem(joueur);
        j++;
        
        const char* name2 = joueurs[i].getName().c_str();
        Button* joueur2 = new Button(QString(name2));
        int cPos = scene->width()/2 + 400;//- franceplayer_j1->boundingRect().width()/2;
        int dPos = 250 + i*200;
        joueur2->setPos(cPos,dPos);
        QSignalMapper* signalMapper2 = new QSignalMapper(this);
        connect(joueur2, SIGNAL(clicked()), signalMapper2, SLOT(map()));
        signalMapper2->setMapping(joueur2, j);
        connect(signalMapper2, SIGNAL(mapped(int)), this, SLOT(select_joueur(int))); 
        scene->addItem(joueur2);
        j++;
    }
    
    Button* playButton = new Button(QString("Start"));
    int kxPos = scene->width()/2 -20 ;//- playButton->boundingRect().width()/2;
    int lyPos = 700;
    playButton->setPos(kxPos,lyPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(selectplayerMenu()));
    scene->addItem(playButton);
    j=0;

    QGraphicsTextItem* j1text = new QGraphicsTextItem(QString("J1"));
    QFont titleFont_j1("comic sans",30);
    j1text->setFont(titleFont_j1);
    int j1txPos = scene->width()/2 - 320;//- titleText->boundingRect().width()/2;
    int j1tyPos = 190;
    j1text->setPos(j1txPos,j1tyPos);
    scene->addItem(j1text);

    QGraphicsTextItem* j2text = new QGraphicsTextItem(QString("J2"));
    QFont titleFont_j2("comic sans",30);
    j2text->setFont(titleFont_j2);
    int j2txPos = scene->width()/2 + 470;//- titleText->boundingRect().width()/2;
    int j2tyPos = 190;
    j2text->setPos(j2txPos,j2tyPos);
    scene->addItem(j2text);
   
}

void Game::select_joueur(int i){
    //std::cout<<"i vaut : "<<i<<std::endl;
    if(i==0) indice_j1 = 0;
    if(i==1) indice_j2 = 0;
    if(i==2) indice_j1 = 1;
    if(i==3) indice_j2 = 1;
    if(i==4) indice_j1 = 2;
    if(i==5) indice_j2 = 2;
}



bool Game::comparaison(std::string name, std::vector<std::string> equipe){
    std::cout << "je suis dans la fonction comparaison" << std::endl;
    for(auto i : equipe){
        //std::cout << "Test comparaison" << std::endl;
        //std::cout << "le nom cherche est :" << name << std::endl;
        //std::cout << "le nom courant est :" << i << std::endl;
        ///std::cout << "la taille de name est" << name.size() << std::endl;
        //std::cout << "la taille de i est" << i.size() << std::endl;
        i.erase(std::remove_if(i.begin(), i.end(), [](unsigned char x){return std::isspace(x);}), i.end());
        if(name == i) {
            return true;
            //std::cout << "je n ai pas retourne true" << std::endl;
        }
    }
    return false;
}


void Game::buyMenu(){

    scene->clear();
    scene->setSceneRect(0,0,1500,768);
    // create the title text
    scene->setBackgroundBrush(QImage(":/Image/Image/Environment/fond_ecran3.png"));
     QGraphicsPixmapItem * french_player = new QGraphicsPixmapItem();
    french_player->setPixmap(QPixmap(":/Image/Image/Player/p1_blue.png"));
    french_player->setPos(100,150);
    QGraphicsPixmapItem * guinean_player = new QGraphicsPixmapItem();
    guinean_player->setPixmap(QPixmap(":/Image/Image/Player/p1_black3.png"));
    guinean_player->setPos(500,150);
    QGraphicsPixmapItem * mexican_player = new QGraphicsPixmapItem();
    mexican_player->setPixmap(QPixmap(":/Image/Image/Player/p1_mex.png"));
    mexican_player->setPos(900,150);
    QGraphicsPixmapItem * american_player = new QGraphicsPixmapItem();
    american_player->setPixmap(QPixmap(":/Image/Image/Player/p1_blond.png"));
    american_player->setPos(1300,150);
    scene->addItem(french_player);
    scene->addItem(guinean_player);
    scene->addItem(mexican_player);
    scene->addItem(american_player);
   
    
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Achat de joueurs"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = scene->width()/2 - 250;//titleText->boundingRect().width()/2;
    int tyPos = 50;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);
    int bxPos = 50;
    int prxPos = 70;
    for(int i =0;i<joueurs_dispo.size();i++){
        Button* playerButton = new Button(QString(joueurs_dispo[i].name.c_str()));
        int byPos = 350;
        playerButton->setPos(bxPos,byPos);
        bxPos +=400;
        QSignalMapper* signalMapper = new QSignalMapper(this);
        connect(playerButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(playerButton, i);
        connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(player_select(int))); 
        scene->addItem(playerButton);

        std::string p = "Prix : ";
        std::string stemp = p + std::to_string(joueurs_dispo[i].prix).c_str();
        QGraphicsTextItem* prix = new QGraphicsTextItem(QString(stemp.c_str()));
        QFont titleFont("comic sans",20);
        prix->setFont(titleFont);
        int pryPos = 450;
        prix->setPos(prxPos,pryPos);
        prxPos += 400;
        scene->addItem(prix);

        
    }

    
    Button* j1 = new Button(QString("J1"));
    int j1xPos = 50;
    int j1yPos = 600;
    j1->setPos(j1xPos,j1yPos);
    connect(j1,SIGNAL(clicked()),this,SLOT(buy_for_j1()));
    scene->addItem(j1);

    
    Button* j2 = new Button(QString("J2"));
    int j2xPos = 50;
    int j2yPos = 650;
    j2->setPos(j2xPos,j2yPos);
    connect(j2,SIGNAL(clicked()),this,SLOT(buy_for_j2()));
    scene->addItem(j2);

    // create the quit button
    Button* returnButton = new Button(QString("Retour"));
    int rxPos = scene->width()/2 -100;// quitButton->boundingRect().width()/2;
    int ryPos = 700;
    returnButton->setPos(rxPos,ryPos);
    connect(returnButton,SIGNAL(clicked()),this,SLOT(selectplayerMenu()));
    scene->addItem(returnButton);

    
        
    QGraphicsTextItem* info = new QGraphicsTextItem(QString("Pour acheter un joueur, appuyer sur le joueur que vous voulez acheter puis sur le bouton du joueur qui va acheter le joueur"));;
    QFont titleFont2("comic sans",10);
    info->setFont(titleFont2);
    int inyPos = 650;
    int inxPos =600;
    info->setPos(inxPos,inyPos);
    scene->addItem(info);

    
}

void Game::player_select(int i ){
    if(i==0) {france_choose=1; std::cout<<"france choisi"<<std::endl;}
    if(i==1) {guinee_choose=1; std::cout<<"guinee choisi"<<std::endl;}
    if(i==2) {mexique_choose=1; std::cout<<"mexique choisi"<<std::endl;}
    if(i==3) {american_choose=1; std::cout<<"american choisi"<<std::endl;}
}

void Game::new_CSV(std::vector<Joueur> j )
{
    std::cout << "je suus dans newCSV" << std::endl;
    for (auto& joueur_courant : j) std::cout << joueur_courant << std::endl;
    std::string final2;
    std::cout<<"creation du fichier"<<std::endl;
    std::ofstream fichier;
    fichier.open("sauvegarde2.csv", std::ios::out | std::ios::trunc);
    int tour = 0;
    for(auto& joueur_courant : j)
    {
            std::string n = joueur_courant.getName();
            n.push_back(';');
            std::string s = std::to_string(joueur_courant.getSolde());
            s.push_back(';');
            std::string temp ;
            std::vector<std::string> e = joueur_courant.getEquipe();
            //for (int i = 0; i < joueur_courant.getEquipe().size(); i++)
            for(auto i : e)
            {
                i.erase(std::remove_if(i.begin(), i.end(), [](unsigned char x){return std::isspace(x);}), i.end());
                std::cout << "e[i] : " << i << std::endl;
                temp += i + ';';  
                //temp.push_back(';');
                std::cout << "temp : " << temp << std::endl;
            }
            std::string final = n + s + temp;
            if(tour==0)final2 = final ;
            else final2 = final2 + "\n" +final ;
            std::cout << final << std::endl;
            tour++;
            temp.clear();
    }
    std::cout << "Voici final 2 :" <<final2 << std::endl;
    fichier << final2 << std::endl;
    final2.clear();
        
}



void Game::buy_for_j1(){
    std::cout<<"joueur 1 veut acheter"<<std::endl;
    for(auto i : joueurs_j1) std::cout << i << std::endl;
    if(france_choose==1){
        std::cout<<"joueur francais choisi"<<std::endl;
        std::string france = "france";
        if(comparaison(france,joueurs_j1)==false){
            QMessageBox::information(this,"Info","Vous pouvez acheter ce joueur si votre solde est suffisant");
            if(indice_j1==0){
                std::cout<<"solde joueur 1 : "<<joueurs[0].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde est : " , std::to_string(joueurs[0].getSolde()).c_str());
                if(joueurs[0].getSolde()>=joueurs_dispo[0].prix){
                    joueurs[0].setSolde(joueurs[0].getSolde()-joueurs_dispo[0].prix);
                    //joueurs[0].getSolde() = joueurs[0].getSolde()-joueurs_dispo[0].prix;
                    std::cout<<"solde joueur 1 : "<<joueurs[0].getSolde()<<std::endl;
                    //joueurs[0].getEquipe().push_back(joueurs_dispo[0]);
                    joueurs[0].setEquipe(joueurs_dispo[0].name);
                    joueurs_j1 = joueurs[0].getEquipe();
                    //std::cout<<"Voici joueur_j1 modifié :"<<std::endl;
                    //for(auto i : joueurs_j1) std::cout << i << std::endl;
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");
                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }

            else if(indice_j1==1){
                std::cout<<"solde joueur 2 : "<<joueurs[1].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde est :" , std::to_string(joueurs[1].getSolde()).c_str());
                if(joueurs[1].getSolde()>=joueurs_dispo[0].prix){
                    joueurs[1].setSolde(joueurs[1].getSolde()-joueurs_dispo[0].prix);
                    std::cout<<"solde joueur 2 : "<<joueurs[1].getSolde()<<std::endl;
                    joueurs[1].setEquipe(joueurs_dispo[0].name);
                    joueurs_j1 = joueurs[1].getEquipe();
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }

            else if(indice_j1==2){
                std::cout<<"solde joueur 3 : "<<joueurs[2].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde solde est : " ,std::to_string(joueurs[2].getSolde()).c_str());
                if(joueurs[2].getSolde()>=joueurs_dispo[0].prix){
                    joueurs[2].setSolde(joueurs[2].getSolde()-joueurs_dispo[0].prix);
                    std::cout<<"solde joueur 3 : "<<joueurs[2].getSolde()<<std::endl;
                    joueurs[2].setEquipe(joueurs_dispo[0].name);
                    joueurs_j1 = joueurs[2].getEquipe();
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");
                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }
        }
        else{
            QMessageBox::information(this,"Erreur","Vous possédez déjà ce joueur");
        }
    }

    if(guinee_choose==1){
        std::cout<<"joueur francais choisi"<<std::endl;
        std::string guinee = "guinee";
        if(comparaison(guinee,joueurs_j1)==false){
            QMessageBox::information(this,"Info","Vous pouvez acheter ce joueur si votre solde est suffisant");
            if(indice_j1==0){
                std::cout<<"solde joueur 1 : "<<joueurs[0].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde est : " , std::to_string(joueurs[0].getSolde()).c_str());
                if(joueurs[0].getSolde()>=joueurs_dispo[1].prix){
                    joueurs[0].setSolde(joueurs[0].getSolde()-joueurs_dispo[1].prix);
                    //joueurs[0].getSolde() = joueurs[0].getSolde()-joueurs_dispo[0].prix;
                    std::cout<<"solde joueur 1 : "<<joueurs[0].getSolde()<<std::endl;
                    //joueurs[0].getEquipe().push_back(joueurs_dispo[0]);
                    joueurs[0].setEquipe(joueurs_dispo[1].name);
                    joueurs_j1 = joueurs[0].getEquipe();
                    //std::cout<<"Voici joueur_j1 modifié :"<<std::endl;
                    //for(auto i : joueurs_j1) std::cout << i << std::endl;
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");
                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }

            else if(indice_j1==1){
                std::cout<<"solde joueur 2 : "<<joueurs[1].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde est :" , std::to_string(joueurs[1].getSolde()).c_str());
                if(joueurs[1].getSolde()>=joueurs_dispo[1].prix){
                    joueurs[1].setSolde(joueurs[1].getSolde()-joueurs_dispo[1].prix);
                    std::cout<<"solde joueur 2 : "<<joueurs[1].getSolde()<<std::endl;
                    joueurs[1].setEquipe(joueurs_dispo[1].name);
                    joueurs_j1 = joueurs[1].getEquipe();
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }

            else if(indice_j1==2){
                std::cout<<"solde joueur 3 : "<<joueurs[2].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde solde est : " ,std::to_string(joueurs[2].getSolde()).c_str());
                if(joueurs[2].getSolde()>=joueurs_dispo[1].prix){
                    joueurs[2].setSolde(joueurs[2].getSolde()-joueurs_dispo[1].prix);
                    std::cout<<"solde joueur 3 : "<<joueurs[2].getSolde()<<std::endl;
                    joueurs[2].setEquipe(joueurs_dispo[1].name);
                    joueurs_j1 = joueurs[2].getEquipe();
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");
                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }
        }
        else{
            QMessageBox::information(this,"Erreur","Vous possédez déjà ce joueur");
        }
    }


    if(mexique_choose==1){
        std::cout<<"joueur francais choisi"<<std::endl;
        std::string mexique = "mexique";
        if(comparaison(mexique,joueurs_j1)==false){
            QMessageBox::information(this,"Info","Vous pouvez acheter ce joueur si votre solde est suffisant");
            if(indice_j1==0){
                std::cout<<"solde joueur 1 : "<<joueurs[0].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde est : " , std::to_string(joueurs[0].getSolde()).c_str());
                if(joueurs[0].getSolde()>=joueurs_dispo[2].prix){
                    joueurs[0].setSolde(joueurs[0].getSolde()-joueurs_dispo[2].prix);
                    //joueurs[0].getSolde() = joueurs[0].getSolde()-joueurs_dispo[0].prix;
                    std::cout<<"solde joueur 1 : "<<joueurs[0].getSolde()<<std::endl;
                    //joueurs[0].getEquipe().push_back(joueurs_dispo[0]);
                    joueurs[0].setEquipe(joueurs_dispo[2].name);
                    joueurs_j1 = joueurs[0].getEquipe();
                    //std::cout<<"Voici joueur_j1 modifié :"<<std::endl;
                    //for(auto i : joueurs_j1) std::cout << i << std::endl;
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");
                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }

            else if(indice_j1==1){
                std::cout<<"solde joueur 2 : "<<joueurs[1].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde est :" , std::to_string(joueurs[1].getSolde()).c_str());
                if(joueurs[1].getSolde()>=joueurs_dispo[2].prix){
                    joueurs[1].setSolde(joueurs[1].getSolde()-joueurs_dispo[2].prix);
                    std::cout<<"solde joueur 2 : "<<joueurs[1].getSolde()<<std::endl;
                    joueurs[1].setEquipe(joueurs_dispo[2].name);
                    joueurs_j1 = joueurs[1].getEquipe();
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }

            else if(indice_j1==2){
                std::cout<<"solde joueur 3 : "<<joueurs[2].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde solde est : " ,std::to_string(joueurs[2].getSolde()).c_str());
                if(joueurs[2].getSolde()>=joueurs_dispo[2].prix){
                    joueurs[2].setSolde(joueurs[2].getSolde()-joueurs_dispo[2].prix);
                    std::cout<<"solde joueur 3 : "<<joueurs[2].getSolde()<<std::endl;
                    joueurs[2].setEquipe(joueurs_dispo[2].name);
                    joueurs_j1 = joueurs[2].getEquipe();
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");
                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }
        }
        else{
            QMessageBox::information(this,"Erreur","Vous possédez déjà ce joueur");
        }
    }


    if(american_choose==1){
        std::cout<<"joueur francais choisi"<<std::endl;
        std::string american = "american";
        if(comparaison(american,joueurs_j1)==false){
            QMessageBox::information(this,"Info","Vous pouvez acheter ce joueur si votre solde est suffisant");
            if(indice_j1==0){
                std::cout<<"solde joueur 1 : "<<joueurs[0].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde est : " , std::to_string(joueurs[0].getSolde()).c_str());
                if(joueurs[0].getSolde()>=joueurs_dispo[3].prix){
                    joueurs[0].setSolde(joueurs[0].getSolde()-joueurs_dispo[3].prix);
                    //joueurs[0].getSolde() = joueurs[0].getSolde()-joueurs_dispo[0].prix;
                    std::cout<<"solde joueur 1 : "<<joueurs[0].getSolde()<<std::endl;
                    //joueurs[0].getEquipe().push_back(joueurs_dispo[0]);
                    joueurs[0].setEquipe(joueurs_dispo[3].name);
                    joueurs_j1 = joueurs[0].getEquipe();
                    //std::cout<<"Voici joueur_j1 modifié :"<<std::endl;
                    //for(auto i : joueurs_j1) std::cout << i << std::endl;
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");
                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }

            else if(indice_j1==1){
                std::cout<<"solde joueur 2 : "<<joueurs[1].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde est :" , std::to_string(joueurs[1].getSolde()).c_str());
                if(joueurs[1].getSolde()>=joueurs_dispo[3].prix){
                    joueurs[1].setSolde(joueurs[1].getSolde()-joueurs_dispo[3].prix);
                    std::cout<<"solde joueur 2 : "<<joueurs[1].getSolde()<<std::endl;
                    joueurs[1].setEquipe(joueurs_dispo[3].name);
                    joueurs_j1 = joueurs[1].getEquipe();
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }

            else if(indice_j1==2){
                std::cout<<"solde joueur 3 : "<<joueurs[2].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde solde est : " ,std::to_string(joueurs[2].getSolde()).c_str());
                if(joueurs[2].getSolde()>=joueurs_dispo[3].prix){
                    joueurs[2].setSolde(joueurs[2].getSolde()-joueurs_dispo[3].prix);
                    std::cout<<"solde joueur 3 : "<<joueurs[2].getSolde()<<std::endl;
                    joueurs[2].setEquipe(joueurs_dispo[3].name);
                    joueurs_j1 = joueurs[2].getEquipe();
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");
                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }
        }
        else{
            QMessageBox::information(this,"Erreur","Vous possédez déjà ce joueur");
        }
    }

    france_choose=0;
    guinee_choose=0;
    mexique_choose=0;
    american_choose=0;
}


void Game::buy_for_j2(){
    std::cout<<"joueur 2 veut acheter"<<std::endl;
    for(auto i : joueurs_j2) std::cout << i << std::endl;
    if(france_choose==1){
        std::cout<<"joueur francais choisi"<<std::endl;
        std::string france = "france";
        if(comparaison(france,joueurs_j2)==false){
            QMessageBox::information(this,"Info","Vous pouvez acheter ce joueur si votre solde est suffisant");
            if(indice_j2==0){
                std::cout<<"solde joueur 1 : "<<joueurs[0].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde est : " , std::to_string(joueurs[0].getSolde()).c_str());
                if(joueurs[0].getSolde()>=joueurs_dispo[0].prix){
                    joueurs[0].setSolde(joueurs[0].getSolde()-joueurs_dispo[0].prix);
                    //joueurs[0].getSolde() = joueurs[0].getSolde()-joueurs_dispo[0].prix;
                    std::cout<<"solde joueur 1 : "<<joueurs[0].getSolde()<<std::endl;
                    //joueurs[0].getEquipe().push_back(joueurs_dispo[0]);
                    joueurs[0].setEquipe(joueurs_dispo[0].name);
                    joueurs_j2 = joueurs[0].getEquipe();
                    //std::cout<<"Voici joueur_j1 modifié :"<<std::endl;
                    //for(auto i : joueurs_j1) std::cout << i << std::endl;
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");
                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }

            else if(indice_j2==1){
                std::cout<<"solde joueur 2 : "<<joueurs[1].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde est :" , std::to_string(joueurs[1].getSolde()).c_str());
                if(joueurs[1].getSolde()>=joueurs_dispo[0].prix){
                    joueurs[1].setSolde(joueurs[1].getSolde()-joueurs_dispo[0].prix);
                    std::cout<<"solde joueur 2 : "<<joueurs[1].getSolde()<<std::endl;
                    joueurs[1].setEquipe(joueurs_dispo[0].name);
                    joueurs_j2 = joueurs[1].getEquipe();
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }

            else if(indice_j2==2){
                std::cout<<"solde joueur 3 : "<<joueurs[2].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde solde est : " ,std::to_string(joueurs[2].getSolde()).c_str());
                if(joueurs[2].getSolde()>=joueurs_dispo[0].prix){
                    joueurs[2].setSolde(joueurs[2].getSolde()-joueurs_dispo[0].prix);
                    std::cout<<"solde joueur 3 : "<<joueurs[2].getSolde()<<std::endl;
                    joueurs[2].setEquipe(joueurs_dispo[0].name);
                    joueurs_j2 = joueurs[2].getEquipe();
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");
                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }
        }
        else{
            QMessageBox::information(this,"Erreur","Vous possédez déjà ce joueur");
        }
    }

    if(guinee_choose==1){
        std::cout<<"joueur francais choisi"<<std::endl;
        std::string guinee = "guinee";
        if(comparaison(guinee,joueurs_j2)==false){
            QMessageBox::information(this,"Info","Vous pouvez acheter ce joueur si votre solde est suffisant");
            if(indice_j1==0){
                std::cout<<"solde joueur 1 : "<<joueurs[0].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde est : " , std::to_string(joueurs[0].getSolde()).c_str());
                if(joueurs[0].getSolde()>=joueurs_dispo[1].prix){
                    joueurs[0].setSolde(joueurs[0].getSolde()-joueurs_dispo[1].prix);
                    //joueurs[0].getSolde() = joueurs[0].getSolde()-joueurs_dispo[0].prix;
                    std::cout<<"solde joueur 1 : "<<joueurs[0].getSolde()<<std::endl;
                    //joueurs[0].getEquipe().push_back(joueurs_dispo[0]);
                    joueurs[0].setEquipe(joueurs_dispo[1].name);
                    joueurs_j2 = joueurs[0].getEquipe();
                    //std::cout<<"Voici joueur_j1 modifié :"<<std::endl;
                    //for(auto i : joueurs_j1) std::cout << i << std::endl;
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");
                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }

            else if(indice_j2==1){
                std::cout<<"solde joueur 2 : "<<joueurs[1].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde est :" , std::to_string(joueurs[1].getSolde()).c_str());
                if(joueurs[1].getSolde()>=joueurs_dispo[1].prix){
                    joueurs[1].setSolde(joueurs[1].getSolde()-joueurs_dispo[1].prix);
                    std::cout<<"solde joueur 2 : "<<joueurs[1].getSolde()<<std::endl;
                    joueurs[1].setEquipe(joueurs_dispo[1].name);
                    joueurs_j2 = joueurs[1].getEquipe();
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }

            else if(indice_j2==2){
                std::cout<<"solde joueur 3 : "<<joueurs[2].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde solde est : " ,std::to_string(joueurs[2].getSolde()).c_str());
                if(joueurs[2].getSolde()>=joueurs_dispo[1].prix){
                    joueurs[2].setSolde(joueurs[2].getSolde()-joueurs_dispo[1].prix);
                    std::cout<<"solde joueur 3 : "<<joueurs[2].getSolde()<<std::endl;
                    joueurs[2].setEquipe(joueurs_dispo[1].name);
                    joueurs_j2 = joueurs[2].getEquipe();
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");
                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }
        }
        else{
            QMessageBox::information(this,"Erreur","Vous possédez déjà ce joueur");
        }
    }


    if(mexique_choose==1){
        std::cout<<"joueur francais choisi"<<std::endl;
        std::string mexique = "mexique";
        if(comparaison(mexique,joueurs_j2)==false){
            QMessageBox::information(this,"Info","Vous pouvez acheter ce joueur si votre solde est suffisant");
            if(indice_j2==0){
                std::cout<<"solde joueur 1 : "<<joueurs[0].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde est : " , std::to_string(joueurs[0].getSolde()).c_str());
                if(joueurs[0].getSolde()>=joueurs_dispo[2].prix){
                    joueurs[0].setSolde(joueurs[0].getSolde()-joueurs_dispo[2].prix);
                    //joueurs[0].getSolde() = joueurs[0].getSolde()-joueurs_dispo[0].prix;
                    std::cout<<"solde joueur 1 : "<<joueurs[0].getSolde()<<std::endl;
                    //joueurs[0].getEquipe().push_back(joueurs_dispo[0]);
                    joueurs[0].setEquipe(joueurs_dispo[2].name);
                    joueurs_j2 = joueurs[0].getEquipe();
                    //std::cout<<"Voici joueur_j1 modifié :"<<std::endl;
                    //for(auto i : joueurs_j1) std::cout << i << std::endl;
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");
                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }

            else if(indice_j2==1){
                std::cout<<"solde joueur 2 : "<<joueurs[1].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde est :" , std::to_string(joueurs[1].getSolde()).c_str());
                if(joueurs[1].getSolde()>=joueurs_dispo[2].prix){
                    joueurs[1].setSolde(joueurs[1].getSolde()-joueurs_dispo[2].prix);
                    std::cout<<"solde joueur 2 : "<<joueurs[1].getSolde()<<std::endl;
                    joueurs[1].setEquipe(joueurs_dispo[2].name);
                    joueurs_j2 = joueurs[1].getEquipe();
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }

            else if(indice_j2==2){
                std::cout<<"solde joueur 3 : "<<joueurs[2].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde solde est : " ,std::to_string(joueurs[2].getSolde()).c_str());
                if(joueurs[2].getSolde()>=joueurs_dispo[2].prix){
                    joueurs[2].setSolde(joueurs[2].getSolde()-joueurs_dispo[2].prix);
                    std::cout<<"solde joueur 3 : "<<joueurs[2].getSolde()<<std::endl;
                    joueurs[2].setEquipe(joueurs_dispo[2].name);
                    joueurs_j2 = joueurs[2].getEquipe();
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");
                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }
        }
        else{
            QMessageBox::information(this,"Erreur","Vous possédez déjà ce joueur");
        }
    }


    if(american_choose==1){
        std::cout<<"joueur francais choisi"<<std::endl;
        std::string american = "american";
        if(comparaison(american,joueurs_j2)==false){
            QMessageBox::information(this,"Info","Vous pouvez acheter ce joueur si votre solde est suffisant");
            if(indice_j2==0){
                std::cout<<"solde joueur 1 : "<<joueurs[0].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde est : " , std::to_string(joueurs[0].getSolde()).c_str());
                if(joueurs[0].getSolde()>=joueurs_dispo[3].prix){
                    joueurs[0].setSolde(joueurs[0].getSolde()-joueurs_dispo[3].prix);
                    //joueurs[0].getSolde() = joueurs[0].getSolde()-joueurs_dispo[0].prix;
                    std::cout<<"solde joueur 1 : "<<joueurs[0].getSolde()<<std::endl;
                    //joueurs[0].getEquipe().push_back(joueurs_dispo[0]);
                    joueurs[0].setEquipe(joueurs_dispo[3].name);
                    joueurs_j2 = joueurs[0].getEquipe();
                    //std::cout<<"Voici joueur_j1 modifié :"<<std::endl;
                    //for(auto i : joueurs_j1) std::cout << i << std::endl;
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");
                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }

            else if(indice_j2==1){
                std::cout<<"solde joueur 2 : "<<joueurs[1].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde est :" , std::to_string(joueurs[1].getSolde()).c_str());
                if(joueurs[1].getSolde()>=joueurs_dispo[3].prix){
                    joueurs[1].setSolde(joueurs[1].getSolde()-joueurs_dispo[3].prix);
                    std::cout<<"solde joueur 2 : "<<joueurs[1].getSolde()<<std::endl;
                    joueurs[1].setEquipe(joueurs_dispo[3].name);
                    joueurs_j2 = joueurs[1].getEquipe();
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }

            else if(indice_j2==2){
                std::cout<<"solde joueur 3 : "<<joueurs[2].getSolde()<<std::endl;
                QMessageBox::information(this,"Info","Votre solde solde est : " ,std::to_string(joueurs[2].getSolde()).c_str());
                if(joueurs[2].getSolde()>=joueurs_dispo[3].prix){
                    joueurs[2].setSolde(joueurs[2].getSolde()-joueurs_dispo[3].prix);
                    std::cout<<"solde joueur 3 : "<<joueurs[2].getSolde()<<std::endl;
                    joueurs[2].setEquipe(joueurs_dispo[3].name);
                    joueurs_j2 = joueurs[2].getEquipe();
                    new_CSV(joueurs);
                    QMessageBox::information(this,"Info","Achat effectué");
                }
                else{
                    QMessageBox::information(this,"Erreur","Solde insuffisant");
                }
            }
        }
        else{
            QMessageBox::information(this,"Erreur","Vous possédez déjà ce joueur");
        }
    }

    france_choose=0;
    guinee_choose=0;
    mexique_choose=0;
    american_choose=0;
}
 */