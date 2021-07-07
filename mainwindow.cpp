#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>

MainWindow::MainWindow(std::string path_of_the_project, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_path_of_the_project = path_of_the_project;
    ui->centralWidget->setLayout(ui->mainLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
