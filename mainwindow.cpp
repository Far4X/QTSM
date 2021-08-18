#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SubClasses/rootaxisdata.h"
#include <string>
#include <iostream>

//ToDo : If the Axis doesn't have child, modify the gui (replace 'percent of sub axes' done by 'is the axis done ?', with a checkbutton istead of the %bar(And modify the spacer))

MainWindow::MainWindow(std::string path_of_the_project, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_path_of_the_project = path_of_the_project;

    m_root_axis = new RootAxisData(m_path_of_the_project);
    m_current_path_in_axes = m_root_axis->getPathAxes();
    std::cout << m_root_axis->getTree() << std::endl;
    std::cout << m_root_axis->getName() << std::endl;

    for (unsigned int i{0}; i < m_root_axis->getChilds()->size(); i++){
        std::cout << "Child nb " << i << " .Name : " << m_root_axis->getChilds()->operator[](i)->getName() << std::endl;
    }

    ui->centralWidget->setLayout(ui->mainLayout);
    ui->labelDescriptionOfTheAxis->setText(QString("This is a very very very long text without any goal, except maybe the fact that it show if I am a good dev, or more precisely, in this case, a good designer, because this text can show me if i done well the display of the description, which is, of course, filled with this text"));
    ui->labelDescriptionOfTheAxis->setWordWrap(true);

    ui->labelHeaderDescription->setText(QString::fromStdString("Description of the current axis : " + m_root_axis->getName()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
