#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QClipboard>
#include <iostream>
#include <sstream>
#include <stack>

class SimpleCalculatorApp : public QWidget {
    Q_OBJECT
public:
    SimpleCalculatorApp(QWidget *parent = nullptr) : QWidget(parent) {
        initUI();
    }

// private slots:
//     void handleButtonClicked();

private:
    QLineEdit *display;
    std::stack<double> operands;
    std::stack<char> operators;

    void initUI() {
        display = new QLineEdit();

        this->resize(500, 600);
        this->setWindowTitle("Simple Calculator");

        QGridLayout *layout = new QGridLayout(this);

        display->setAlignment(Qt::AlignRight);
        display->setFixedHeight(75);
        QFont font = display->font();
        font.setPointSize(40);
        display->setFont(font);
        display->setReadOnly(true);

        layout->addWidget(display, 0, 0, 1, 4);

        const QStringList buttonLabels = {
            "7", "8", "9", "/",
            "4", "5", "6", "*",
            "1", "2", "3", "-",
            "0", ".", "=", "+",
            "C", "Copy"
        };

        QVector<QPushButton *> buttons;
        for (int i = 0; i < buttonLabels.size(); ++i) {
            QPushButton *button = new QPushButton(buttonLabels[i]);
            int row = i / 4 + 1;
            int col = i % 4;
            if (buttonLabels[i] == "Copy") {
                button->setFixedSize(125, 75);
                button->setToolTip("On click: Copies the content of Display to system clipboard!");
            } else {
                button->setFixedSize(125, 75);
            }
            QFont font = button->font();
            font.setPointSize(18);
            button->setFont(font);
            layout->addWidget(button, row, col);
            buttons.append(button);

            if (buttonLabels[i] == "C") {
                QObject::connect(button, &QPushButton::clicked, this, &SimpleCalculatorApp::clearDisplay);
            } else if (buttonLabels[i] == "Copy") {
                QObject::connect(button, &QPushButton::clicked, this, &SimpleCalculatorApp::copyDisplay);
            } else if (buttonLabels[i] != "=") {
                QObject::connect(button, &QPushButton::clicked, this, &SimpleCalculatorApp::appendToDisplay);
            } else {
                QObject::connect(button, &QPushButton::clicked, this, &SimpleCalculatorApp::handleButtonClicked);
            }
        }

        setLayout(layout);
    }

    void clearDisplay() {
        display->clear();
    }

    void copyDisplay() {
        QString textToCopy = display->text();
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(textToCopy);
    }

    void appendToDisplay() {
        QPushButton *button = qobject_cast<QPushButton *>(sender());
        if (button)
            display->setText(display->text() + button->text());
    }

    void handleButtonClicked() {
        QString expression = display->text();
        double result = evalExpression(expression.toStdString());
        display->setText(QString::number(result));
    }

    double evalExpression(const std::string &expression) {
        // std::istringstream iss(expression.toStdString());
        std::istringstream iss(expression);
        std::stack<double> operands;
        std::stack<char> operators;

        char currentChar;
        while (iss >> currentChar) {
            if (isdigit(currentChar) || currentChar == '.') {
                iss.putback(currentChar);
                double operand;
                iss >> operand;
                operands.push(operand);
            } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
                while (!operators.empty() && (
                           (currentChar != '*' && currentChar != '/' && operators.top() == '*') ||
                           (currentChar != '*' && currentChar != '/' && operators.top() == '/') ||
                           (currentChar == '+' || currentChar == '-') && (operators.top() == '+' || operators.top() == '-')
                           )) {
                    char op = operators.top();
                    operators.pop();
                    double operand2 = operands.top();
                    operands.pop();
                    double operand1 = operands.top();
                    operands.pop();

                    if (op == '+') {
                        operands.push(operand1 + operand2);
                    } else if (op == '-') {
                        operands.push(operand1 - operand2);
                    } else if (op == '*') {
                        operands.push(operand1 * operand2);
                    } else if (op == '/') {
                        if (operand2 == 0) {
                            std::cerr << "Error: Division by zero." << std::endl;
                            return 0; // Or handle the error as needed
                        }
                        operands.push(operand1 / operand2);
                    }
                }
                operators.push(currentChar);
            }
        }

        while (!operators.empty()) {
            char op = operators.top();
            operators.pop();
            double operand2 = operands.top();
            operands.pop();
            double operand1 = operands.top();
            operands.pop();

            if (op == '+') {
                operands.push(operand1 + operand2);
            } else if (op == '-') {
                operands.push(operand1 - operand2);
            } else if (op == '*') {
                operands.push(operand1 * operand2);
            } else if (op == '/') {
                if (operand2 == 0) {
                    std::cerr << "Error: Division by zero." << std::endl;
                    return 0; // Or handle the error as needed
                }
                operands.push(operand1 / operand2);
            }
        }

        if (!operands.empty()) {
            return operands.top();
        } else {
            std::cerr << "Error: No result." << std::endl;
            return 0; // Or handle the error as needed
        }
    }
};

#include "main.moc"
// Include the moc file for Qt's meta-object system;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    SimpleCalculatorApp calculator;
    calculator.show();

    return app.exec();
}
