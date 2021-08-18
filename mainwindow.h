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

private:
    Ui::MainWindow *ui;
    std::string m_path_of_the_project;
    std::string m_current_path_in_axes;
    RootAxisData *m_root_axis;
};

#endif // MAINWINDOW_H
