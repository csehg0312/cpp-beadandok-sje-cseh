#include "clickablerectangle.h"


ClickableRectangle::ClickableRectangle(qreal x, qreal y, qreal width, qreal height, QString label, int index, QGraphicsItem* parent)
    : QGraphicsRectItem(x, y, width, height, parent), label(label), index(index) {
    // qDebug() << "New created";
    // qDebug() << "Text: " << label;

    QDir wDir = QDir::current();
    wDir.cdUp();
    QString currentPath = wDir.absolutePath();

    // qDebug() << currentPath + "/chess_version1/figs/wq.png";

    bool loadSuccess = true;
    loadSuccess &= imageList[White_Queen].load(currentPath +    "/chess_version1/figs/wq.png");
    loadSuccess &= imageList[White_King].load(currentPath +     "/chess_version1/figs/wk.png");
    loadSuccess &= imageList[White_Bishop].load(currentPath +   "/chess_version1/figs/wb.png");
    loadSuccess &= imageList[White_Rook].load(currentPath +     "/chess_version1/figs/wt.png");
    loadSuccess &= imageList[White_Knight].load(currentPath +   "/chess_version1/figs/wh.png");
    loadSuccess &= imageList[White_Pawn].load(currentPath +     "/chess_version1/figs/wg.png");
    loadSuccess &= imageList[Black_Queen].load(currentPath +    "/chess_version1/figs/bq.png");
    loadSuccess &= imageList[Black_King].load(currentPath +     "/chess_version1/figs/bk.png");
    loadSuccess &= imageList[Black_Bishop].load(currentPath +   "/chess_version1/figs/bb.png");
    loadSuccess &= imageList[Black_Rook].load(currentPath +     "/chess_version1/figs/bt.png");
    loadSuccess &= imageList[Black_Knight].load(currentPath +   "/chess_version1/figs/bh.png");
    loadSuccess &= imageList[Black_Pawn].load(currentPath +     "/chess_version1/figs/bg.png");

    if (!loadSuccess) {
        qDebug() << "Error loading some pixmap";
    }

}

void ClickableRectangle::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        isClicked = true;
        qDebug() << "Clicked" << index;
        update();

    }
    QGraphicsRectItem::mousePressEvent(event);
}

void ClickableRectangle::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::LeftButton && isClicked) {
        isClicked = false;
        // Handle mouse release event if needed
    }
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void ClickableRectangle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::gray);
    painter->drawRect(boundingRect());
    if ((index >= 0) && (index <= 63)){
        if (index < 16){



            QChar qcharlabel = label.at(0);
            char charlabel = qcharlabel.toLatin1();

            switch(charlabel) {
            case 'P':
                painter->drawPixmap(boundingRect().toRect(), imageList[White_Pawn].scaled(boundingRect().size().toSize(), Qt::KeepAspectRatio));
                break;
            case 'R':
                painter->drawPixmap(boundingRect().toRect(), imageList[White_Rook].scaled(boundingRect().size().toSize(), Qt::KeepAspectRatio));
                break;
            case 'H':
                painter->drawPixmap(boundingRect().toRect(), imageList[White_Knight].scaled(boundingRect().size().toSize(), Qt::KeepAspectRatio));
                break;
            case 'K':
                painter->drawPixmap(boundingRect().toRect(), imageList[White_King].scaled(boundingRect().size().toSize(), Qt::KeepAspectRatio));
                break;
            case 'Q':
                painter->drawPixmap(boundingRect().toRect(), imageList[White_Queen].scaled(boundingRect().size().toSize(), Qt::KeepAspectRatio));
                break;
            case 'B':
                painter->drawPixmap(boundingRect().toRect(), imageList[White_Bishop].scaled(boundingRect().size().toSize(), Qt::KeepAspectRatio));
                break;
            default:
                qDebug() << "Not implemented";
                break;
            }
        }else if (index >= 16){
            if (index < 48){

            }
            else if (index >= 48) {
                QChar qcharlabel = label.at(0);
                char charlabel = qcharlabel.toLatin1();

                switch(charlabel) {
                case 'P':
                    painter->drawPixmap(boundingRect().toRect(), imageList[Black_Pawn].scaled(boundingRect().size().toSize(), Qt::KeepAspectRatio));
                    break;
                case 'R':
                    painter->drawPixmap(boundingRect().toRect(), imageList[Black_Rook].scaled(boundingRect().size().toSize(), Qt::KeepAspectRatio));
                    break;
                case 'H':
                    painter->drawPixmap(boundingRect().toRect(), imageList[Black_Knight].scaled(boundingRect().size().toSize(), Qt::KeepAspectRatio));
                    break;
                case 'K':
                    painter->drawPixmap(boundingRect().toRect(), imageList[Black_King].scaled(boundingRect().size().toSize(), Qt::KeepAspectRatio));
                    break;
                case 'Q':
                    painter->drawPixmap(boundingRect().toRect(), imageList[Black_Queen].scaled(boundingRect().size().toSize(), Qt::KeepAspectRatio));
                    break;
                case 'B':
                    painter->drawPixmap(boundingRect().toRect(), imageList[Black_Bishop].scaled(boundingRect().size().toSize(), Qt::KeepAspectRatio));
                    break;
                default:
                    qDebug() << "Not implemented";
                    break;
                }
            }

        }
    }

}
