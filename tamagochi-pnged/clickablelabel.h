#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QDebug>

class ClickableLabel : public QLabel {
    Q_OBJECT
public:
    explicit ClickableLabel(QWidget *parent = nullptr);


signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
};
//Q_DECLARE_OPERATORS_FOR_FLAGS(ClickableLabel::MyFlag)

#endif // CLICKABLELABEL_H
