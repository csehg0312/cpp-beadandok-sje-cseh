#include "widget.h"

Widget::Widget(QWidget *parent) : BaseWidget(parent) {}

void Widget::onLabelClicked() {
    // Implement specific behavior for the derived class
    // (Optional: Call the BaseWidget implementation if needed)

    BaseWidget::onLabelClicked(); // Call the base class implementation

    // Add additional functionality specific to Widget class


}




