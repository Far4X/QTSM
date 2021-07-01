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
    explicit ModifyOptionsProject(std::string project_name, std::map<std::string, std::string> &projects_dict, class ChooseAProject *widget_of_the_project, QWidget *parent = nullptr);
    ~ModifyOptionsProject();
    void updatePathLabel();

public slots:
    void resetLineEdit();
    void changeProjectName();
    void changeFileName();

private:
    Ui::ModifyOptionsProject *ui;
    class ChooseAProject *m_widget_of_the_project;
    std::string m_project_name;
    std::map<std::string, std::string> *m_projects_dict;
};

#endif // MODIFYOPTIONSPROJECT_H
