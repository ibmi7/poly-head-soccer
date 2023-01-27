
# PolyHeadSoccer

Le projet de jeu PolyHeadSoccer vise à créer un jeu en local opposant deux joueurs représentant Messi et Ronaldo. Le but du jeu est d'acheter tous les joueurs disponibles sur le marché en premier. Les joueurs peuvent gagner des pièces en jouant des matchs et en les remportant. Il y a une fonctionnalité d'achat de joueurs qui permet aux joueurs d'utiliser leurs pièces pour acheter des joueurs supplémentaires pour renforcer leur équipe. Le jeu est contrôlé à l'aide des touches directionnelles du clavier pour Messi et les touches ZQSD pour Ronaldo.


## Installation

Il est nécessaire d'avoir les librairies Qt pour pouvoir compiler et exécuter correctement le jeu. Voici les étapes de son installation.

```bash
  sudo apt-get install build-essential libgl1-mesa-dev 
  sudo apt-get install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
  sudo apt-get install qtmultimedia5-dev libqt5multimediawidgets5 libqt5multimedia5-plugins libqt5multimedia5

```
Tapez ces commandes dans un terminal linux afin de pouvoir compiler le projet.
## Documentation

Ouvrez le fichier index.html inclus dans le dossier doc pour avoir accès à une documentation détaillée.


## Usage

Pour compiler le programme, tapez la commande ` make ` sur le terminal dans le dossier source du projet.
Pour l'éxecuter, tapez la commande `./HeadSoccer` sur le terminal.

Lorsque vous lancez le jeu pour la première fois, les deux joueurs ont un solde de 100 pièces chacuns, et uniquement 1 personnage dans leur équipe (personnage France). Pour jouer, cliquez sur le bouton Play. Vous arriverez sur l'écran de sélection du personnage. A gauche, les personnages de Messi (contrôlés avec les touches directionnelles du clavier). A droite, les personnages de Ronaldo (contrôlés avec les touches ZSQD du clavier). Sélectionnez un personnage de chaque côté et appuyez sur Play pour lancer une partie.

L'objectif est d'être le premier à marquer 3 buts. Le gagnant reçoit 100 pièces en récompenses.

Pour acheter des joueurs, il suffit de se rendre dans le Market. Dans ce menu, le solde de chaque joueurs est affiché, ainsi que la liste des personnages disponibles à l'achat ainsi que leur prix. Pour acheter un personnage, il faut cliquer sur le bouton correspondant à ce dernier. Si le solde est suffisant, l'achat est effectué, sinon un message box apparaît pour signaler que le solde est insuffisant.

Pour remettre les compteurs à 0, cliquer sur le bouton Reset au lancement du jeu. Les deux joueurs reviendront à leur état de base.


## Running Tests

Les tests sont effectués au début du Main. On teste la création et la destruction d'un personnage, ainsi que d'un Joueur.


## Authors

- [@ibmi7](https://www.github.com/ibmi7)
- [@Skyoussef](https://www.github.com/Skyoussef)

