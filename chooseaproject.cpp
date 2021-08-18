#include "chooseaproject.h"
#include "ui_chooseaproject.h"
#include "mainwindow.h"
#include "commonfunctions.h"
#include <QString>
#include <QInputDialog>
#include <QFileDialog>
#include <string>
#include <iostream>
#include <map>
#include <QObject>
#include <QMessageBox>

ChooseAProject::ChooseAProject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseAProject)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("QTSM - Choose a project"));
    QObject::connect(ui->pushButtonValidCurrentProject, SIGNAL(clicked()), this, SLOT(projectSelected()));
    QObject::connect(ui->pushButtonDeleteCurrentProject, SIGNAL(clicked()), this, SLOT(deleteThisProject()));
    QObject::connect(ui->pushButtonOption, SIGNAL(clicked()), this, SLOT(modifyThisProject()));
    QObject::connect(ui->pushButtonNewProject, SIGNAL(clicked()), this, SLOT(createNewProject()));
    m_dict_projects = getDictFic();
}


ChooseAProject::~ChooseAProject()
{
    delete ui;
    if (m_project_win != nullptr){
        delete m_project_win;
    }
    if (m_modify_project_win != nullptr){
        m_modify_project_win ->close();
        delete m_modify_project_win;
    }
}


void ChooseAProject::addElemInList(std::string elem){
   ui->comboBoxChooseAProject->addItem(QString::fromStdString(elem));
}


void ChooseAProject::refreshList(){
    ui->comboBoxChooseAProject->clear();
    for(auto &item : m_dict_projects){
        addElemInList(item.first);
    }
}


void ChooseAProject::setCurrentElemInList(QString elem){
    ui->comboBoxChooseAProject->setCurrentText(elem);
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
    std::string path_of_the_project = m_dict_projects[project_chosen];
    m_project_win = new MainWindow(path_of_the_project, this);
    m_project_win->show();
}


void ChooseAProject::modifyThisProject(){
    std::string project_chosen(ui->comboBoxChooseAProject->currentText().toStdString());
    std::string path_file_project = m_dict_projects[project_chosen];
    m_modify_project_win = new ModifyOptionsProject(project_chosen, m_dict_projects, this);
    m_modify_project_win->show();
}


void ChooseAProject::createNewProject(){
    std::string project_name = QInputDialog::getText(this, tr("Choose a name for your project"), tr("Name for your project : ")).toStdString();
    std::string project_path = QFileDialog::getSaveFileName(this, "Choose a file for your project", getHomeDir(), "qtsm files (*.qtsm)").toStdString();
    if (project_name != "" && project_path != ""){
        system(("touch " + project_path).c_str());
        m_dict_projects[project_name] = project_path;
        ui->comboBoxChooseAProject->addItem(QString::fromStdString(project_name));
        rewriteFile(m_dict_projects);
    }
}


void ChooseAProject::close(){
    qApp->quit();
}
