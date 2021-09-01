#include "axisdatacontentprinter.h"
#include "ui_axisdatacontentprinter.h"
#include <QInputDialog>
#include <QString>
#include <QMessageBox>
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
    ui->labelName->setText(QString::fromStdString(m_content_to_print->getName()));
    ui->textBrowser->setText(QString::fromStdString(m_content_to_print->getDescription()));

    QObject::connect(ui->pushButtonChangeName, SIGNAL(clicked()), this, SLOT(renameAxisData()));
    QObject::connect(ui->pushButtonChangeDescription, SIGNAL(clicked()), this, SLOT(redescribeAxisData()));
}

AxisDataContentPrinter::~AxisDataContentPrinter()
{
    delete ui;
}

void AxisDataContentPrinter::renameAxisData(){
    std::string new_name = QInputDialog::getText(this, tr("Choose a new name for this axis"), tr("Type here the new name : ")).toStdString();
    if (new_name != ""){
        if (m_content_to_print->getParent() != nullptr){
            if (m_content_to_print->getParent()->haveAChildNamed(new_name)){
                QMessageBox::warning(this, tr("Impossible to rename with this name"), QString::fromStdString("The axis parent of this one , " + m_content_to_print->getParent()->getName() + ", have already a sub-axis named " + new_name));
            }
            else {
                m_content_to_print->rename(new_name);
            }
        }
        else {
            m_content_to_print->rename(new_name);

        }
        QMessageBox::information(this, tr("Operation ended successfully"), tr("The axis had just been renamed successfully"));
        ui->labelName->setText(QString::fromStdString(m_content_to_print->getName()));

    }
    else {
        QMessageBox::warning(this, tr("Impossible to rename with no name"), QString::fromStdString("The name shouldn't be empty"));
    }
}

void AxisDataContentPrinter::redescribeAxisData(){
    std::string new_desc = QInputDialog::getMultiLineText(this, QString::fromStdString("Choose a new desc for " + m_content_to_print->getName()), tr("Type here the new description"), QString::fromStdString(m_content_to_print->getDescription())).toStdString();
    m_content_to_print->setDescription(new_desc);
    QMessageBox::information(this, tr("Operation ended successfully"), tr("The axis had just been redescribed successfully"));
    ui->textBrowser->setText(QString::fromStdString(m_content_to_print->getDescription()));

}


