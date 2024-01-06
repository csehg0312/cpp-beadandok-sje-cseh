
#ifndef WIDGET_H
#define WIDGET_H

#include "basewidget.h"

class Widget : public BaseWidget {
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);

protected:
    void onLabelClicked() override;

};

#endif
