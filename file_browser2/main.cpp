#include <QApplication>
#include <QDir>
#include <QListWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QPixmap>
#include <QImage>
#include <QLabel>
#include <QImageReader>
#include <QDebug>
#include <QFileInfo>
#include <QScreen>
#include <QRect>

class ImageViewer : public QWidget {
    Q_OBJECT

public:
    ImageViewer(QWidget *parent = nullptr) : QWidget(parent) {

        listWidget = new QListWidget(this);
        backButton = new QPushButton("Back", this);
        currentPathLabel = new QLabel(this);
        showImage = new QLabel(this);
        closeButton = new QPushButton("x", this);

        layout = new QGridLayout(this);
        layout->addWidget(backButton, 0, 0);
        layout->addWidget(currentPathLabel, 0, 1);
        layout->addWidget(listWidget, 1, 0);
        layout->addWidget(showImage, 1, 1);

        QPixmap notFoundImage;
        if (QFileInfo::exists(notFoundImagePath)) {
            qDebug() << "Image loading from: " << notFoundImagePath;
            notFoundImage.load(notFoundImagePath);
            showImage->setPixmap(notFoundImage);
        } else {
            qDebug() << "Image File not found at: " << notFoundImagePath;
        }
        qDebug() << "Trying to add to layout";

        connect(backButton, &QPushButton::clicked, this, &ImageViewer::goBack);
        connect(listWidget, &QListWidget::itemDoubleClicked, this, &ImageViewer::openItem);
        connect(closeButton, &QPushButton::clicked, this, &ImageViewer::closeImage);

        setCurrentDirectory(QDir::homePath());
    }

private slots:
    void goBack() {
        QDir backDir(currentDirectory);
        backDir.cdUp();
        setCurrentDirectory(QString(backDir.absolutePath()));
    }

    void openItem(QListWidgetItem *item) {

        QString itemName = item->text();
        QString newPath = currentDirectory.filePath(itemName);

        if (QFileInfo(newPath).isDir()) {

            setCurrentDirectory(newPath);
        } else {
            try {
                QImageReader imageReader(newPath);

                if (!imageReader.canRead()) {

                    throw std::runtime_error("Unsupported image format or corrupted file");
                }

                // Load the image
                openedImage.load(newPath);
                showImage->setPixmap(QPixmap::fromImage(openedImage));
                // update();
                layout->addWidget(closeButton,3,3);
                closeButton->setText("x");

                qDebug("Selected file: %s", qPrintable(newPath));
            } catch (const std::exception &e) {
                // Catch and handle the exception
                qDebug() << "Error loading image:" << e.what();
            }
        }
    }

    void closeImage() {
        showImage->clear();
        layout->removeWidget(closeButton);
    }
private:
    void setCurrentDirectory(const QString &path) {

        currentDirectory.setPath(path);
        currentPathLabel->setText("Mappa: " + path);

        listWidget->clear();

        QStringList entries = currentDirectory.entryList();
        for (const QString &entry : entries) {
            if ((entry != ".") && (entry != "..")) {
                QListWidgetItem *item = new QListWidgetItem(entry);
                listWidget->addItem(item);
            }
        }
    }

    QGridLayout *layout;
    QPixmap notFoundImage;
    QImage openedImage;
    QListWidget *listWidget;
    QPushButton *backButton;
    QPushButton *closeButton;
    QLabel *showImage;
    QLabel *currentPathLabel;
    QDir currentDirectory;
    QDir workingDir = QDir::currentPath();
    QString notFoundImagePath = workingDir.absolutePath() + "/Sources/noimage.jpeg";
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QScreen *openedScreen = QGuiApplication::primaryScreen();
    QRect screenRect = openedScreen->geometry();
    int scWidth = screenRect.width();
    int scHeight = screenRect.height();

    ImageViewer imageViewer;
    imageViewer.setFixedSize(scWidth, scHeight-150);
    imageViewer.show();

    return app.exec();
}

#include "main.moc"
