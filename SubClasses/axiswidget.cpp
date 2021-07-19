#include "axiswidget.h"
#include "ui_axiswidget.h"

AxisWidget::AxisWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AxisWidget)
{
    ui->setupUi(this);
}

AxisWidget::~AxisWidget()
{
    delete ui;
}
