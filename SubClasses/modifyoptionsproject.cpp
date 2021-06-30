#include "modifyoptionsproject.h"
#include "ui_modifyoptionsproject.h"
#include "chooseaproject.h"
#include "commonfunctions.h"
#include <QString>
#include <QObject>
#include <QInputDialog>
#include <map>
#include <string>
#include <iostream>

ModifyOptionsProject::ModifyOptionsProject(std::string project_name, std::map<std::string, std::string> &projects_dict, ChooseAProject *widget_of_the_project, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyOptionsProject)
{
    ui->setupUi(this);
    m_widget_of_the_project = widget_of_the_project;
    m_project_name = project_name;
    m_projects_dict = &projects_dict;
    ui->label->setText(QString::fromStdString("You are modifing the project named '" + m_project_name + "'"));
    this->setWindowTitle(QString::fromStdString("QTSM - Modify project : " + m_project_name));
    ui->lineEditChangeProjectName->insert(QString::fromStdString(m_project_name));

    ui->labelShowPath->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    ui->labelShowPath->setWordWrap(true);
    ui->labelShowPath->setText(QString::fromStdString("Current path of the project : \n" + m_projects_dict->operator[](m_project_name)));

    QObject::connect(ui->buttonBoxChangeName, SIGNAL(rejected()), this, SLOT(resetLineEdit()));
    QObject::connect(ui->buttonBoxChangeName, SIGNAL(accepted()), this, SLOT(changeProjectName()));
    QObject::connect(ui->buttonChangeName, SIGNAL(clicked()), this, SLOT(changeFileName()));
}

ModifyOptionsProject::~ModifyOptionsProject(){
    delete ui;
}

void ModifyOptionsProject::resetLineEdit(){
    ui->lineEditChangeProjectName->setText(QString::fromStdString(m_project_name));
}

void ModifyOptionsProject::changeProjectName(){
    QString new_name_of_the_project = ui->lineEditChangeProjectName->text();
    std::string path_holder = m_projects_dict->operator[](m_project_name);
    m_projects_dict->erase(m_project_name);
    m_projects_dict->operator[](new_name_of_the_project.toStdString()) = path_holder;
    m_widget_of_the_project->refreshList();
    m_widget_of_the_project->setCurrentElemInList(new_name_of_the_project);
    rewriteFile(*m_projects_dict);
}

void ModifyOptionsProject::changeFileName(){
    std::cout << "OK3" << std::endl;
    QString new_file_name_qstring = QInputDialog::getText(this, tr("Choose a new name for the file"), tr("Files name:"));
    std::string new_file_name = new_file_name_qstring.toStdString();
    std::string old_path = (*m_projects_dict)[m_project_name];
    //Scinder le path en plusieurs parties, mettre dans vect, file name -> dernier elem de la liste, new path = reste + new_name
}
