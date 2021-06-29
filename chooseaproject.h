#ifndef CHOOSEAPROJECT_H
#define CHOOSEAPROJECT_H

#include <QWidget>
#include <string>
#include <map>
#include "mainwindow.h"

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

public slots:
    void projectSelected();
    void deleteThisProject();
    void close();

private:
    Ui::ChooseAProject *ui;
    MainWindow *m_project_win = nullptr;
    std::map <std::string, std::string> m_dict_projects;
};

#endif // CHOOSEAPROJECT_H
