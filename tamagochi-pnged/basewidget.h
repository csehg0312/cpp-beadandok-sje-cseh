#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include <QDir>
#include <QDebug>
#include "clickablelabel.h"

enum Emotion { Happy, Sad, Blushing };

class BaseWidget : public QWidget {
    Q_OBJECT

public:
    explicit BaseWidget(QWidget *parent = nullptr);
    virtual ~BaseWidget();

protected:
    ClickableLabel* label;
    QPixmap scaledHappy, scaledSad, scaledBlushing;
    int imSize = 750;
    Emotion currentEmotion = Happy;

    void changeEmotion();

    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void onLabelClicked();
    bool eventFilter(QObject *obj, QEvent *event);


    void loadImages();
    void mouseMoveEvent(QMouseEvent * event) override;

signals:
    void widgetPressEvent();
};

#endif // BASEWIDGET_H
