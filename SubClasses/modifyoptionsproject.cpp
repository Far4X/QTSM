#include "modifyoptionsproject.h"
#include "ui_modifyoptionsproject.h"
#include <QString>
#include <map>

ModifyOptionsProject::ModifyOptionsProject(std::string project_name, std::map<std::string, std::string> &projects_dict, QWidget *master, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyOptionsProject)
{
    ui->setupUi(this);
    m_master = master;
    m_project_name = project_name;
    m_projects_dict = &projects_dict;
    ui->label->setText(QString::fromStdString("You'r modifing the project named '" + m_project_name + "'"));
    this->setWindowTitle(QString::fromStdString("QTSM - Modify project : " + m_project_name));
}

ModifyOptionsProject::~ModifyOptionsProject()
{
    delete ui;
}
