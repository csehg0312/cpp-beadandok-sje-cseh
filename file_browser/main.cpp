#include <QApplication>
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QTreeWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QPushButton>
#include "dirworker.h"
#include "keyenterpress.h"

int numofFiles;

class MyApp : public QWidget {
public:
    MyApp(QWidget *parent = nullptr) : QWidget(parent) {
        initUI();
    }
    QString dirWorkerDir;

private slots:
    void listSystemFiles(const QString &directory) {
        QDir dir(directory);
        if (!dir.exists()) {
            qDebug() << "Directory not found";
            return;
        }

        QStringList fileList = dir.entryList(QDir::AllEntries);
        numofFiles = fileList.size();
        qDebug() << "System Files in " << directory << ": ";
        foreach (const QString &file, fileList) {
            if ((file != ".") and (file != "..")){
                listWidget->addItem(file);
            }
        }
    }



public slots:
    void onDirectoryChanged(const QString &newDirectory) {
        qDebug() << "Received signal >>>" << newDirectory;
        // QDir newDir(newDirectory);
        // listSystemFiles(newDir);
    }


private:

    QListWidget *listWidget;
    dirWorker workerInstance;

    void initUI() {
        listWidget = new QListWidget();

        QPushButton* backButton = new QPushButton();
        backButton->setText("<-");
        connect(backButton, &QPushButton::clicked, this, [=] (){
            qDebug() << "Backbutton";
            dirWorker worker;
            worker.upADir();
        });

        // dirWorker workerInstance;
        dirWorkerDir = workerInstance.directory;
        connect(&workerInstance, &dirWorker::directoryChanged, this, &MyApp::onDirectoryChanged);
        qDebug() << "Connected: " << connect(&workerInstance, &dirWorker::directoryChanged, this, &MyApp::onDirectoryChanged);

        keyEnterPress* enter = new keyEnterPress();
        listWidget->installEventFilter(enter);


        QLineEdit* inputDirectory = new QLineEdit;
        inputDirectory->installEventFilter(enter);
        QWidget *treeWidget = new QWidget;
        QGridLayout *mainLayout = new QGridLayout(treeWidget);


        inputDirectory->setText(dirWorkerDir);

        QFileSystemModel model;
        model.setRootPath(QDir::currentPath()); // Set the root path to the desired directory

        // Create the tree view and set the model
        QTreeView *treeView = new QTreeView;
        treeView->setModel(&model);

        // Set the root index for the tree view
        QModelIndex rootIndex = model.index(QDir::currentPath());
        treeView->setRootIndex(rootIndex);

        mainLayout->addWidget(treeView, 0, 1);
        mainLayout->addWidget(listWidget, 0, 0);
        mainLayout->addWidget(inputDirectory, 1,1);
        mainLayout->addWidget(backButton, 1,0);
        setLayout(mainLayout);

        setWindowTitle("Folder Opener");
        setGeometry(300, 300, 800, 500);
        listSystemFiles(dirWorkerDir);
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MyApp myapp;
    myapp.show();
    return a.exec();
}
