#include "chooseaproject.h"
#include "ui_chooseaproject.h"
#include "mainwindow.h"
#include "commonfunctions.h"
#include <QString>
#include <string>
#include <iostream>
#include <QObject>

ChooseAProject::ChooseAProject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseAProject)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("QTSM - (Choose a project)"));
    QObject::connect((ui->pushButtonValidCurrentProject), SIGNAL(clicked()), this, SLOT(projectSelected()));
}

ChooseAProject::~ChooseAProject()
{
    delete ui;
    delete m_new_win;
}

void ChooseAProject::addElemInList(std::string elem){
   ui->comboBoxChooseAProject->addItem(QString::fromStdString(elem));
}

void ChooseAProject::projectSelected(){
    std::string project_chosen(ui->comboBoxChooseAProject->currentText().toStdString());
    this->hide();
    m_new_win = new MainWindow(project_chosen, this);
    m_new_win->show();
}

void ChooseAProject::close(){
    const char *home_dir(getHomeDir());
    std::cout << home_dir << std::endl;

    qApp->quit();
}
