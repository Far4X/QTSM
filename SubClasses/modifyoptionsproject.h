#ifndef MODIFYOPTIONSPROJECT_H
#define MODIFYOPTIONSPROJECT_H

#include <QWidget>
#include <string>
#include <map>

namespace Ui {
class ModifyOptionsProject;
}

class ModifyOptionsProject : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyOptionsProject(std::string project_name, std::map<std::string, std::string> &projects_dict, QWidget *parent = nullptr);
    ~ModifyOptionsProject();

private:
    Ui::ModifyOptionsProject *ui;
    std::string m_project_name;
    std::map<std::string, std::string> *m_projects_dict;
};

#endif // MODIFYOPTIONSPROJECT_H
