#include <QApplication>
#include <iostream>
#include "chessboard.h"



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    int boardSize = 750;
    ChessBoard chessBoard(boardSize);
    chessBoard.show();

    return app.exec();
}
