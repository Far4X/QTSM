#include "chooseaproject.h"
#include "ui_chooseaproject.h"
#include "mainwindow.h"
#include "commonfunctions.h"
#include <QString>
#include <string>
#include <iostream>
#include <QObject>
#include <QMessageBox>

ChooseAProject::ChooseAProject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseAProject)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("QTSM - (Choose a project)"));
    QObject::connect((ui->pushButtonValidCurrentProject), SIGNAL(clicked()), this, SLOT(projectSelected()));
    QObject::connect((ui->pushButtonDeleteCurrentProject), SIGNAL(clicked()), this, SLOT(deleteThisProject()));
    m_dict_projects = getDictFic();
}


ChooseAProject::~ChooseAProject()
{
    delete ui;
    if (m_project_win != nullptr){
        delete m_project_win;
    }
}


void ChooseAProject::addElemInList(std::string elem){
   ui->comboBoxChooseAProject->addItem(QString::fromStdString(elem));
}


void ChooseAProject::deleteThisProject(){
   const std::string project_to_delete(ui->comboBoxChooseAProject->currentText().toStdString());
   const std::string message("Are you sure that you wan to delete the " + project_to_delete + " project ? The file at the emplacement " + m_dict_projects[project_to_delete] + " will be deleted too.");
   int answer(QMessageBox::question(this, "Delete a project ?", QString::fromStdString(message), QMessageBox::Yes | QMessageBox::No));
   if (answer == QMessageBox::Yes){
       const std::string cmd("rm " + m_dict_projects[project_to_delete]);
       system(cmd.c_str());
       m_dict_projects.erase(project_to_delete);
       rewriteFile(m_dict_projects);
       ui->comboBoxChooseAProject->removeItem(ui->comboBoxChooseAProject->currentIndex());
   }
}



void ChooseAProject::projectSelected(){
    std::string project_chosen(ui->comboBoxChooseAProject->currentText().toStdString());
    this->hide();
    m_project_win = new MainWindow(project_chosen, this);
    m_project_win->show();
}


void ChooseAProject::close(){
    qApp->quit();
}
