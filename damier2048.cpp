#include <iostream>
#include <random>
#include <QMessageBox>

#include "damier2048.h"
#include "params.h"
#include "losedialog.h"
#include "windialog.h"
#include <vector>
#include <array>

Damier2048::Damier2048(QObject* parent) : QObject(parent), DamierExc(Lx, Ly, 2048, 0) {
    score = 0;
    highScore = 0;
    InitJeu();
}

/*********************************************************************************************
 * Initialisation : InitJeu()
 *
 * Description : Cette fonction initialise la matrice du jeu (vide initialement) en occupant
 * deux cases aléatoires de la matrice.
 *
 * Retour : Modifie la matrice par effet de bord.
 *
 *********************************************************************************************/

void Damier2048::InitJeu(){
    for (int i=0; i<2; i++)
        this->RandomFill();
    viewMatrice();
}

/*********************************************************************************************
 * Relancer une partie : Restart()
 *
 * Description : Remet le jeu dans son état initial pour recommencer une partie.
 *
 * Retour : Modifie la matrice par effet de bord.
 *
 *********************************************************************************************/

void Damier2048::restart(){
    for(int i=0; i<Ly; i++)
        for(int j=0; j<Lx; j++)
            this->T[i][j] = 0;
    InitJeu();
    viewMatrice();
    score = 0;
    emit scoreChanged();
    viewMatrice();
}

/*********************************************************************************************
 * Génération de nouvelles cases : RandomFill()
 *
 * Description : Cette fonction génère un 2 ou un 4 dans un emplacement inoccupé de la matrice.
 *
 * Retour : Modifie la matrice par effet de bord.
 *
 *********************************************************************************************/

void Damier2048::RandomFill(){
    std::random_device rd;
    std::mt19937 gen(rd());

    // Définition de la distribution d'entiers
    std::uniform_int_distribution<> distrib(0, 3); // Distribution uniforme entre 0 et 3 inclus

    // Ajout d'une valeur aléatoire (2 ou 4) dans une case qui vaut 0
    while (true) {
        int row = distrib(gen); // Choix aléatoire de la ligne
        int col = distrib(gen); // Choix aléatoire de la colonne

        if (this->T[row][col] == 0) {
            std::uniform_int_distribution<> distrib_val(0, 1); // Distribution uniforme entre 0 et 1 inclus
            int valeur = (distrib_val(gen) == 0) ? 2 : 4; // Choix aléatoire de la valeur (2 ou 4)

            this->Set(row, col, valeur); // Ajout de la valeur dans la case choisie
            break; // Sortir de la boucle
        }
    }
}

/**********************************************************************************************
 * Déplacement : Move
 *
 * Description : Cette fonction permet d'actualiser la matrice en cas de déplacement des éléments
 * dans une direction.
 *
 * Paramètre :
 *   - Direction direction : Enumeration forte de quatre directions (LEFT, UP, DOWN, RIGHT)
 *
 * Retour : Modifie la matrice par effet de bord.
 *
 *********************************************************************************************/

void Damier2048::Move(Direction direction){
    // On sauvegarde la matrice initiale
    array<array<int, 4>, 4> matrix{};
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            matrix[i][j] = this->T[i][j];
        }
    }
    matrices.push_back(matrix);

    bool b = false; // On change ce booléen si on effectue pas de mouvement de case
    int di = 0, dj = 0;
    switch (direction){
        case Direction::LEFT:
            dj = -1;
            break;
        case Direction::RIGHT:
            dj = 1;
            break;
        case Direction::UP:
            di = -1;
            break;
        case Direction::DOWN:
            di = 1;
            break;
    }

    for (int i = 0; i < Ly; i++) {
        for (int j = 0; j < Lx; j++) {
            int ni = i + di;
            int nj = j + dj;
            if (this->T[i][j] != 0){
                while (ni >= 0 && ni < Ly && nj >= 0 && nj < Lx && this->T[ni][nj] == 0) {
                    ni += di;
                    nj += dj;
                }
                if (ni >= 0 && ni < Ly && nj >= 0 && nj < Lx && this->T[ni][nj] == this->T[i][j]) {
                    this->T[ni][nj] *= 2;
                    score += this->T[ni][nj];
                    if (this->T[ni][nj] == 2048) {
                        WinDialog *winDialog = new WinDialog();
                        connect(winDialog, &WinDialog::accepted, this, &Damier2048::restart);
                        connect(winDialog, &QDialog::finished, winDialog, &QObject::deleteLater);
                        winDialog->exec();
                    }
                    if (score > highScore) {
                        highScore = score;
                    }
                    this->T[i][j] = 0;
                    b = true;
                }
                else {
                    ni -= di;
                    nj -= dj;
                    if (ni != i || nj != j) {
                        this->T[ni][nj] = this->T[i][j];
                        this->T[i][j] = 0;
                        b = true;
                    }
                }
            }
        }
    }
    if (b){
        RandomFill(); // si la partie a evoluée on rajoute une case occupée
        emit scoreChanged();
        emit highScoreChanged();
        if (isLost()){
            LoseDialog *loseDialog = new LoseDialog();
            connect(loseDialog, &LoseDialog::accepted, this, &Damier2048::restart);
            connect(loseDialog, &QDialog::finished, loseDialog, &QObject::deleteLater);
            loseDialog->exec();
        }
        viewMatrice();
    }
    else {
        matrices.pop_back();
    }
}

void Damier2048::left(){
    Move(Direction::LEFT);
}

void Damier2048::right(){
    Move(Direction::RIGHT);
}

void Damier2048::up(){
    Move(Direction::UP);
}

void Damier2048::down(){
    Move(Direction::DOWN);
}

/*********************************************************************************************
 * Défaite : isLost()
 *
 * Description : Cette fonction renvoie true si la partie est perdue false sinon. Elle est
 * appelée avant chaque mouvement.
 *
 * Retour : Modifie la matrice par effet de bord.
 *
 *********************************************************************************************/

bool Damier2048::isLost(){
      // Vérifier s'il y a une case vide
      for (int i = 0; i < Ly; i++) {
        for (int j = 0; j < Lx; j++) {
          if (this->T[i][j] == 0) {
            return false;
          }
        }
      }

      // Vérifier s'il y a des mouvements possibles
      for (int i = 0; i < Ly; i++) {
        for (int j = 0; j < Lx; j++) {
          if (i < Ly-1 && this->T[i][j] == this->T[i+1][j]) {
            return false;
          }
          if (j < Lx-1 && this->T[i][j] == this->T[i][j+1]) {
            return false;
          }
        }
      }
      return true;
}

/*********************************************************************************************
 * viewMatrice : viewMatrice()
 *
 * Description : Cette fonction sérialise les élément du damier dans une liste et convertit les
 * éléments en QString.
 *
 * Retour :
 *
 *********************************************************************************************/

void Damier2048::viewMatrice(){
    QList<QString> cListTemp;
    QList<QString> nListTemp;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cListTemp.append(Color(this->T[i][j]));
            if (this->T[i][j] != 0)
                nListTemp.append(QString::number(this->T[i][j]));
            else {
                nListTemp.append("");
            }
        }
    }
    nList = nListTemp;
    cList = cListTemp;
    emit nbChanged();
    emit crChanged();
    emit nbcrChanged();
}

QList<QString> Damier2048::readNumber(){
    return nList;
}

QList<QString> Damier2048::readColor(){
    return cList;
}

QList<QString> Damier2048::readNumberColor(){
    return tList;
}


/*********************************************************************************************
 * Couleur : Color(int n)
 *
 * Description : Cette fonction renvoie la couleur associée à un nombre de la matrice
 *
 * Retour : String
 *
 *********************************************************************************************/

QString Color(int n){
    QString color;
    switch(n){
        case 0:
            color = "#CDC1B4";
            break;
        case 2:
            color = "#EEE4DA";
            break;
        case 4:
            color = "#EDE0C8";
            break;
        case 8:
            color = "#F2B179";
            break;
        case 16:
            color = "#F59563";
            break;
        case 32:
            color = "#F67C5F";
            break;
        case 64:
            color = "#F65E3B";
            break;
        case 128:
            color = "#EDCF72";
            break;
        case 256:
            color = "#EDCC61";
            break;
        case 512:
            color = "#EDC850";
            break;
        case 1024:
            color = "#EDC53F";
            break;
        case 2048:
            color = "#EDC22E";
            break;
        default:
            color = "#CDC1B4";
            break;
    }
    return color;
}

/*********************************************************************************************
 * readMatrice : readScore()
 *
 * Description : Cette fonction renvoie le score et la convertit en QString.
 *
 * Retour : QString.
 *
 *********************************************************************************************/

QString Damier2048::readScore() {
    return QString::number(score);
}

/*********************************************************************************************
 * readMatrice : readHighScore()
 *
 * Description : Cette fonction renvoie le meilleur score et la convertit en QString.
 *
 * Retour : QString.
 *
 *********************************************************************************************/

QString Damier2048::readHighScore() {
    return QString::number(highScore);
}


/*********************************************************************************************
 * readMatrice : undo()
 *
 * Description : Revient au coup précédent
 *
 * Retour : Modifie la matrice
 *
 *********************************************************************************************/

void Damier2048::undo(){
    if (!matrices.empty()) {
        array<array<int, 4>, 4> lastMatrix = matrices.back();
        matrices.pop_back();
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                this->T[i][j] = lastMatrix[i][j];
            }
        }
        viewMatrice();
    }
}
