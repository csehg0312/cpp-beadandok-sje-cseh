#include "dirworker.h"

dirWorker::dirWorker() {}

void dirWorker::downADir(QString string) {
    // QDir cdirectory);

    QString completePath = QDir::cleanPath(directory + "/" + string);
    QDir complete(completePath);
    QString newDirectory = QString(complete.path());
    qDebug() << "Emitting signal >>> " << newDirectory;
    emit directoryChanged(newDirectory);
}

void dirWorker::upADir() {

    QDir currentDir(directory);
    if (currentDir.cdUp()) {
        // qDebug() << "Moved up a directory";
        QString newDirectory = QString(currentDir.path());
        qDebug() << "Emitting signal >>> " << newDirectory;
        emit directoryChanged(newDirectory);
    }else{
        qDebug() << "Cannot move up - its not leaf directory!";
    }

}

void dirWorker::changeCDir(QString* cDir) {
    if (cDir) {
        // qDebug() << directory;
        QString directoryPath = *cDir;
        QDir newDir(directoryPath);
        QFileInfo fInfo(newDir.path());
        if ((newDir.exists()) && (fInfo.isDir())){
            QString newDirectory = QString(newDir.path());
            qDebug() << "Emitting signal >>> " << newDirectory;
            emit directoryChanged(newDirectory);
        }

    }
}
