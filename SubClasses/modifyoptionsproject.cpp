#include "modifyoptionsproject.h"
#include "ui_modifyoptionsproject.h"
#include "chooseaproject.h"
#include "commonfunctions.h"
#include <QString>
#include <QObject>
#include <QInputDialog>
#include <map>
#include <vector>
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
    updatePathLabel();

    QObject::connect(ui->buttonBoxChangeName, SIGNAL(rejected()), this, SLOT(resetLineEdit()));
    QObject::connect(ui->buttonBoxChangeName, SIGNAL(accepted()), this, SLOT(changeProjectName()));
    QObject::connect(ui->buttonChangeName, SIGNAL(clicked()), this, SLOT(changeFileName()));
}

ModifyOptionsProject::~ModifyOptionsProject(){
    delete ui;
}

void ModifyOptionsProject::updatePathLabel(){
    ui->labelShowPath->setText(QString::fromStdString("Current path of the project : \n" + m_projects_dict->operator[](m_project_name)));
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
    QString new_file_name_qstring = QInputDialog::getText(this, tr("Choose a new name for the file"), tr("Files name:"));
    std::string new_file_name = new_file_name_qstring.toStdString();
    std::string old_path = (*m_projects_dict)[m_project_name],new_path;
    while (old_path[old_path.size()-1] != 'm'){
        old_path.pop_back();
    }
    std::vector<std::string> list_folder;
    list_folder.push_back("");
    unsigned long place_f(0);
    for (unsigned int i(0); i < old_path.size(); i++){
        if (old_path[i] != '\n' || old_path[i] != '\r'){
            if (old_path[i] == '/'){
                if (i != 0){
                    place_f ++;
                    list_folder.push_back("");
                }
            }
            list_folder[place_f].push_back(old_path[i]);
        }
    }
    for (unsigned int i(0); i < list_folder.size()-1; i++){
        new_path += list_folder[i];
    }
    new_path += ("/" + new_file_name + ".qtsm");
    (*m_projects_dict)[m_project_name] = new_path;
    std::string cmd("mv " + old_path + " " + new_path);
    system(cmd.c_str());
    rewriteFile(*m_projects_dict);
    updatePathLabel();
}
