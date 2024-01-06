#ifndef CLICKABLERECTITEM_H
#define CLICKABLERECTITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QDir>
#include <QPixmap>

class ClickableRectangle : public QGraphicsRectItem {
public:
    ClickableRectangle(qreal x, qreal y, qreal width, qreal height, QString label, int index, QGraphicsItem* parent = nullptr);
    enum PlayerSkins {
        White_Queen,
        White_King,
        White_Rook,
        White_Knight,
        White_Bishop,
        White_Pawn,
        Black_Queen,
        Black_King,
        Black_Rook,
        Black_Knight,
        Black_Bishop,
        Black_Pawn,
        Num_Images = 12
    };

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

// signals:
//     void clicked();

private:
    QPixmap imageList[Num_Images];
    PlayerSkins currentImage;
    QString label;
    int index;
    bool isClicked;
};

#endif // CLICKABLERECTITEM_H
