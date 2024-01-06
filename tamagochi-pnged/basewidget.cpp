#include "basewidget.h"
#include <QGridLayout>
#include <QSize>

BaseWidget::BaseWidget(QWidget *parent) : QWidget(parent) {
    label = new ClickableLabel(this);
    label->setFixedSize(imSize, imSize);

    connect(this, &BaseWidget::widgetPressEvent, label, &ClickableLabel::clicked);
    connect(label, &ClickableLabel::clicked, this, &BaseWidget::onLabelClicked);

    loadImages();

    if (currentEmotion == Happy) {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &BaseWidget::changeEmotion);
        timer->start(5000);
    }
    label->installEventFilter(this);
}

BaseWidget::~BaseWidget() {
    delete label;
}

void BaseWidget::changeEmotion() {
    if (currentEmotion == Happy) {
        label->setPixmap(scaledSad);
        currentEmotion = Sad;
        update();
    }

    label->setScaledContents(true);
    label->show();
}

void BaseWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (currentEmotion == Happy)
        painter.drawPixmap(0, 0, scaledHappy);
    else if (currentEmotion == Sad)
        painter.drawPixmap(0, 0, scaledSad);
    else
        painter.drawPixmap(0, 0, scaledBlushing);
}

void BaseWidget::mousePressEvent(QMouseEvent *event) {
    emit widgetPressEvent();
    QWidget::mousePressEvent(event);
}

void BaseWidget::onLabelClicked() {
    if (currentEmotion == Sad) {
        currentEmotion = Happy;
        label->setPixmap(scaledHappy);
        update();
    }

    label->setScaledContents(true);
    label->show();
}

bool BaseWidget::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        qDebug() << "Mouse move" << mouseEvent->pos().x() << mouseEvent->pos().y();
    }
    return false;
}

void BaseWidget::mouseMoveEvent(QMouseEvent *event) {

    qDebug() << "Mouse moved within the widget";
    QWidget::mouseMoveEvent(event);
}

void BaseWidget::loadImages() {
    QDir wDir = QDir::current();
    wDir.cdUp();
    QString currentPath = wDir.absolutePath();

    QPixmap happyImage(currentPath + "/tamagochi-pnged/happy.png");
    QPixmap sadImage(currentPath + "/tamagochi-pnged/sad.png");
    QPixmap blushingImage(currentPath + "/tamagochi-pnged/blushing.png");

    if (happyImage.isNull() || sadImage.isNull() || blushingImage.isNull()) {
        qDebug() << "Error loading images!";
    } else {
        scaledHappy = happyImage.scaled(QSize(imSize, imSize));
        scaledSad = sadImage.scaled(QSize(imSize, imSize));
        scaledBlushing = blushingImage.scaled(QSize(imSize, imSize));
    }
}
