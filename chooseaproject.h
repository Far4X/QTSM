#ifndef CHOOSEAPROJECT_H
#define CHOOSEAPROJECT_H

#include <QWidget>
#include <string>
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
    void close();

private:
    Ui::ChooseAProject *ui;
    MainWindow *m_new_win;
};

#endif // CHOOSEAPROJECT_H
