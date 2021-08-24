#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include "SubClasses/rootaxisdata.h"
#include "SubClasses/axisdata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(std::string path_of_the_project, QWidget *parent = nullptr);
    ~MainWindow();
    void updateView();

public slots :
    void changeAxisWithButton();
    void changeAxisToMaster();
    void checkBoxClicked(bool state);
    void createNewChild();

private:
    Ui::MainWindow *ui;
    std::vector<QWidget*> m_widgets_when_no_child;
    std::vector<QWidget*> m_widgets_when_child;
    std::string m_path_of_the_project;
    std::string m_current_path_in_axes;
    RootAxisData *m_root_axis;
    AxisData *m_current_axis;
};

#endif // MAINWINDOW_H
