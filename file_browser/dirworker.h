#ifndef DIRWORKER_H
#define DIRWORKER_H
#include <QDir>
#include <QObject>
#include <QFileInfo>

class dirWorker : public QObject
{
    Q_OBJECT

public:
    QString directory = QDir::homePath();

    dirWorker();

public slots:
    void downADir(QString string);
    void upADir();
    void changeCDir(QString* cDir);

signals:
    void directoryChanged(const QString& newDirectory);
};
#endif // DIRWORKER_H
