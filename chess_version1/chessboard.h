#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>

#include <QColor>


class ChessBoard
{
public:
    ChessBoard(int size);
    void show();
    int tileSize;

private:
    QGraphicsScene* scene;
    QGraphicsView* view;

    void addBabuk();
    void drawBoard();
};

#endif // CHESSBOARD_H
