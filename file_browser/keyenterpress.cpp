
#include "keyenterpress.h"
#include "dirworker.h"
#include <QDebug>


// keyEnterPress::keyEnterPress() {

// }


bool keyEnterPress::eventFilter(QObject* obj, QEvent* event) {
    dirWorker worker;
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);

        if (QLineEdit* lineEdit  = qobject_cast<QLineEdit*>(obj)) {
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ){
                handleLineEdit(lineEdit);
                return true;
            }
        }

        if (QListWidget* listWidget  = qobject_cast<QListWidget*>(obj)) {
            if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ){
                QListWidgetItem* currentItem = listWidget->currentItem();

                if (currentItem) {
                    QString itemText = currentItem->text();
                    // qDebug() << itemText;
                    handleUpADirectory(itemText);
                }
                return true;
            }
        }

        if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
            qDebug() << "Enter pressed";
            worker.upADir();
            qDebug() << worker.directory;
        } else {
            return QObject::eventFilter(obj, event);
        }
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
    return false;
}

void keyEnterPress::handleLineEdit(QLineEdit* lineEdit){
    QString text = lineEdit->text();

    handleChangeADirectory(text);
}


void keyEnterPress::handleUpADirectory(const QString& currentItem){
    // qDebug() << currentItem;
    dirWorker worker;
    worker.downADir(currentItem);
}

void keyEnterPress::handleChangeADirectory(const QString& text){
    qDebug() << text;

    QString* textPtr = new QString(text);

    dirWorker worker;
    worker.changeCDir(textPtr);
}

