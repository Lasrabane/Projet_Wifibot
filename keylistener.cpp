/*#include "keylistener.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"
#include "Qwebengineview"
#include <QKeyEvent>
#include <QObject>

keyListener::keyListener()
{
}

bool keyListener::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if ( (key->key()==Qt::Key_Enter) ) {
            QString contenu = vitesse_robot->text();
            //qDebug() << vitesse_robot->text();
            return QObject::eventFilter(obj, event);
        }
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
    return false;
}
*/
