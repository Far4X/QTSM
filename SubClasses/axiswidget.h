#ifndef AXISWIDGET_H
#define AXISWIDGET_H

#include <QWidget>

namespace Ui {
class AxisWidget;
}

class AxisWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AxisWidget(QWidget *parent = nullptr);
    ~AxisWidget();

private:
    Ui::AxisWidget *ui;
};

#endif // AXISWIDGET_H
