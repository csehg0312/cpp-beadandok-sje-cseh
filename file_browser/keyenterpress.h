#ifndef KEYENTERPRESS_H
#define KEYENTERPRESS_H

#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QApplication>
#include <QCoreApplication>

class keyEnterPress : public QObject
{
    Q_OBJECT
// public:
//     keyEnterPress();

private:
    void handleLineEdit(QLineEdit* lineEdit);
    // void handlelistWidget(QListWidget* listWidget, QKeyEvent* key);
    void handleUpADirectory(const QString& currentItem);
    void handleChangeADirectory(const QString& text);
    // void CtrlUEventKeyPress();

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // KEYENTERPRESS_H
