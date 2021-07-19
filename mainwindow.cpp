#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SubClasses/axiswidget.h"
#include <string>

MainWindow::MainWindow(std::string path_of_the_project, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_path_of_the_project = path_of_the_project;
    ui->centralWidget->setLayout(ui->mainLayout);
    for (int i(0); i < 5; i++) {
        m_list_axes.push_back(new AxisWidget(ui->axesArea));
    }
}

MainWindow::~MainWindow()
{
    for (unsigned long i = 0; i < m_list_axes.size(); i++){
        delete m_list_axes[i];
    }
    delete ui;
}
