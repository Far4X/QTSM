#include "chooseaproject.h"
#include "ui_chooseaproject.h"
#include "mainwindow.h"
#include "QString"
#include "string"

ChooseAProject::ChooseAProject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseAProject)
{
    ui->setupUi(this);
}

ChooseAProject::~ChooseAProject()
{
    delete ui;
}

void ChooseAProject::addElemInList(std::string elem){
   ui->comboBoxChooseAProject->addItem(QString::fromStdString(elem));
}

void ChooseAProject::projectSelected(){
    std::string project_chosen(ui->comboBoxChooseAProject->currentText().toStdString());
}
