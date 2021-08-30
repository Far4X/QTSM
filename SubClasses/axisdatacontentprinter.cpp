#include "axisdatacontentprinter.h"
#include "ui_axisdatacontentprinter.h"
#include <iostream>

AxisDataContentPrinter::AxisDataContentPrinter(AxisData *content_to_print, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AxisDataContentPrinter)
{
    ui->setupUi(this);
    m_content_to_print = content_to_print;
    this->setLayout(ui->verticalLayout1);
    std::string title {"Content of " + m_content_to_print->getName()};
    this->setWindowTitle(QString::fromStdString(title));

}

AxisDataContentPrinter::~AxisDataContentPrinter()
{
    delete ui;
}
