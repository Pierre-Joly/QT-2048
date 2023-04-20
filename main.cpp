#include <iostream>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include "damier2048.h"

using namespace std;

int main(int argc, char *argv[]){
    #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif
    QApplication app(argc, argv);
    Damier2048 D;

    QIcon icon(":/icon.png");
    app.setWindowIcon(icon);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml")); // Cette ligne définit l'URL du fichier QML à charger. Le préfixe qrc: indique que le fichier est inclus dans les ressources de l'application. Le nom du fichier est main.qml.

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection); //Cette ligne connecte un signal émis par QQmlApplicationEngine
    // lorsqu'un objet QML est créé, à une fonction lambda qui quitte l'application si l'objet
    // n'a pas été créé avec succès. La connexion est effectuée en utilisant la méthode statique connect() de QObject.
    engine.rootContext()->setContextProperty("vueObjet", &D);
    engine.load(url);

    return app.exec();
}


/* TODO :
 *
 * !! Comprendre pourquoi le constructeur affiche une erreur
 * ! Implémenter le coup en arrière (constructeur de recopie)
 * ! Mettre des exceptions
 * ! Voir ce qu'il se passe si on dépasse la borne 2048
 * !! Mettre un pop up pour la défaite
 *
 */


