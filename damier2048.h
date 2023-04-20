#ifndef DAMIER2048_H
#define DAMIER2048_H

#include "damierexc.h"
#include <QObject>
#include <QString> // Include the QString header
#include <vector>
#include <array>

enum class Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

struct Case {
    QList<QString> n;
    QList<QString> c;
}; // Structure pour renvoyer deux listes pour définir une case (nombre, couleur)

class Damier2048 : public QObject, public DamierExc
{
    Q_OBJECT

public:
    Damier2048(QObject *parent = nullptr);
    void RandomFill();
    void Move(Direction direction);
    Q_INVOKABLE void restart(); // Q_INVOKABLE pour pouvoir appeler la fonction depuis main.qml
    bool isLost();
    Q_PROPERTY(QList<QString> number READ readNumber NOTIFY nbChanged) // change la valeur des nombres sur les cases
    Q_PROPERTY(QList<QString> color READ readColor NOTIFY crChanged)
    Q_PROPERTY(QList<QString> number_color READ readNumberColor NOTIFY nbcrChanged)
    void viewMatrice();
    QList<QString> readNumber();
    QList<QString> readColor();
    QList<QString> readNumberColor();
    Q_PROPERTY(QString scoreQML READ readScore NOTIFY scoreChanged);
    Q_PROPERTY(QString highScoreQML READ readHighScore NOTIFY highScoreChanged);
    QString readScore();
    QString readHighScore();
    Q_INVOKABLE void left();
    Q_INVOKABLE void right();
    Q_INVOKABLE void up();
    Q_INVOKABLE void down();
    Q_INVOKABLE void undo();
protected:
    void InitJeu();
private:
    vector<array<array<int, 4>, 4>> matrices;
    int score;
    int highScore;
signals:
    void nbChanged();
    void crChanged();
    void nbcrChanged();
    void scoreChanged();
    void highScoreChanged();
private:
    QList<QString> nList;
    QList<QString> cList;
    QList<QString> tList;

};

QString Color(int n);

#endif
