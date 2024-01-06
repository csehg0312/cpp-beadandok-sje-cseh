#include "chessboard.h"
#include "QPushButton"
#include "QGridLayout"
#include "QVBoxLayout"
#include "QString"


#include "./clickablerectangle.h"



ChessBoard::ChessBoard(int size) {
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    view->setWindowTitle("Chess Board");
    view->setFixedSize(size, size);



    drawBoard();
    addBabuk();
}

void ChessBoard::show() {
    view->show();
}




void ChessBoard::addBabuk(){
    const QStringList playerLabels = {
        "R","H","B","K","Q","B","H","R",
        "P","P","P","P","P","P","P","P",
        "","","","","","","","",
        "","","","","","","","",
        "","","","","","","","",
        "","","","","","","","",
        "P","P","P","P","P","P","P","P",
        "R","H","B","K","Q","B","H","R"
    };



    int row = 8;
    int col = 8;
    tileSize = view->width() / col;
    // QVector<QPushButton *> jatekTer;


    for (int i = 0; i < row ; ++i){
        for (int j = 0; j < col; ++j){

            int index = i * col + j; // Calculate the index for one-dimensional array

            // QString label = playerLabels[index];
            // qDebug() << index;

            ClickableRectangle* jatekos = new ClickableRectangle(j * tileSize, i * tileSize, tileSize, tileSize, playerLabels[index], index);

            scene->addItem(jatekos);
        }

    }


}

void ChessBoard::drawBoard() {
    int row = 8, col = 8;
    tileSize = view->width() / col;

    const QStringList Alphabet = {
      "A","B","C","D","E","F","G","H"
    };

    QColor color1 = QColor(255, 255, 255); // Feher negyzet
    QColor color2 = QColor(0, 0, 0);  // Fekete negyzet

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            QColor color = (i + j) % 2 == 0 ? color1 : color2;
            QGraphicsRectItem* square = new QGraphicsRectItem(j * tileSize, i * tileSize, tileSize, tileSize);
            square->setBrush(QBrush(color));
            QString plate;
            plate.append(Alphabet[j]);
            plate.append(QString().number(i+1));
            square->setToolTip(plate);
            scene->addItem(square);
        }
    }
}
