#ifndef CHOOSEAPROJECT_H
#define CHOOSEAPROJECT_H

#include <QWidget>
#include <string>
#include <map>
#include "mainwindow.h"
#include "SubClasses/modifyoptionsproject.h"

namespace Ui {
class ChooseAProject;
}

class ChooseAProject : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseAProject(QWidget *parent = nullptr);
    ~ChooseAProject();
    void addElemInList(std::string elem);
    void refreshList();
    void setCurrentElemInList(QString elem);

public slots:
    void projectSelected();
    void deleteThisProject();
    void modifyThisProject();
    void close();

private:
    Ui::ChooseAProject *ui;
    MainWindow *m_project_win = nullptr;
    ModifyOptionsProject *m_modify_project_win = nullptr;
    std::map <std::string, std::string> m_dict_projects;
};

#endif // CHOOSEAPROJECT_H
