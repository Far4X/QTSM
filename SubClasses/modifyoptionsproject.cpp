#include "modifyoptionsproject.h"
#include "ui_modifyoptionsproject.h"
#include "chooseaproject.h"
#include "commonfunctions.h"
#include <QString>
#include <QObject>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <map>
#include <vector>
#include <string>
#include <iostream>

//Functions out of the class

std::string *removeExtraChars(std::string *string, char last_char = 'm'){
    while ((*string)[string->size()-1] != last_char){
        string->pop_back();
    }
    return string;
}

std::vector<std::string> putPathInList(std::string &path){
    std::vector<std::string> list_dir;
    list_dir.push_back("");
    unsigned long place_f(0);
    for (unsigned int i(0); i < path.size(); i++){
        if (path[i] != '\n' || path[i] != '\r'){
            if (path[i] == '/'){
                if (i != 0){
                    place_f ++;
                    list_dir.push_back("");
                }
            }
            list_dir[place_f].push_back(path[i]);
        }
    }
    return list_dir;
}

//Functions in the class

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
    QObject::connect(ui->buttonChangeFolder, SIGNAL(clicked()), this, SLOT(changeProjectFolder()));
    QObject::connect(ui->buttonChangeFile, SIGNAL(clicked()), this, SLOT(changeProjectFile()));
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
    m_project_name = new_name_of_the_project.toStdString();
    m_widget_of_the_project->refreshList();
    m_widget_of_the_project->setCurrentElemInList(new_name_of_the_project);
    rewriteFile(*m_projects_dict);
}

void ModifyOptionsProject::changeFileName(){
    QString new_file_name_qstring = QInputDialog::getText(this, tr("Choose a new name for the file"), tr("Files name:"));
    std::string new_file_name = new_file_name_qstring.toStdString();
    std::string old_path = (*m_projects_dict)[m_project_name], new_path;
    old_path = *(removeExtraChars(&old_path));
    std::vector<std::string> list_folder;
    list_folder = putPathInList(old_path);

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

void ModifyOptionsProject::changeProjectFolder(){
    QString directory = QFileDialog::getExistingDirectory(this, "Select a new directory :", getHomeDir());
    if (directory.toStdString() != ""){
        std::string old_path = (*m_projects_dict)[m_project_name], new_path;
        old_path = *(removeExtraChars(&old_path));

        std::vector<std::string> list_folder;

        list_folder = putPathInList(old_path);
        new_path = directory.toStdString() + list_folder[list_folder.size()-1];
        (*m_projects_dict)[m_project_name] = new_path;
        std::string cmd("mv " + old_path + " " + new_path);
        system(cmd.c_str());
        rewriteFile(*m_projects_dict);
        updatePathLabel();
    }

}

void ModifyOptionsProject::changeProjectFile(){
    std::string new_path = QFileDialog::getOpenFileName(this, tr("Select the new .qtsm for this project"), getHomeDir(), tr(".QTSM files (*.qtsm)")).toStdString();
    if (new_path != ""){
        std::string message("Do you want to delete the old file ?");
        int answer(QMessageBox::question(this, "Delete a project ?", QString::fromStdString(message), QMessageBox::Yes | QMessageBox::No));
        if (answer == QMessageBox::Yes){
            const std::string cmd("rm " + (*m_projects_dict)[m_project_name]);
            system(cmd.c_str());
        }
        (*m_projects_dict)[m_project_name] = new_path;
        rewriteFile(*m_projects_dict);
        updatePathLabel();
    }
}
