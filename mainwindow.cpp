#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SubClasses/rootaxisdata.h"
#include <string>
#include <QInputDialog>
#include <QMessageBox>
#include <iostream>

//ToDo : If the Axis doesn't have child, modify the gui (replace 'percent of sub axes' done by 'is the axis done ?', with a checkbutton istead of the %bar(And modify the spacer))

MainWindow::MainWindow(std::string path_of_the_project, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_path_of_the_project = path_of_the_project;

    m_root_axis = new RootAxisData(m_path_of_the_project);
    m_current_axis = m_root_axis;
    m_current_path_in_axes = m_root_axis->getPathAxes();
    std::cout << m_root_axis->getTree() << std::endl;

    for (unsigned int i{0}; i < m_root_axis->getChilds()->size(); i++){
        std::cout << "Child nb " << i << ". Name : " << m_root_axis->getChilds()->operator[](i)->getName() << std::endl;
    }

    m_root_axis->rename("WorkingTest");
    m_root_axis->saveTree(m_path_of_the_project);

    ui->centralWidget->setLayout(ui->mainLayout);

    ui->labelDescriptionOfTheAxis->setWordWrap(true);
    ui->progressBar->setRange(0, 100);

    ui->labelHeaderDescription->setText(QString::fromStdString("Description of the current axis : "));

    m_widgets_when_child.push_back(ui->comboBox);
    m_widgets_when_child.push_back(ui->progressBar);
    m_widgets_when_child.push_back(ui->pushButtonChangeToChild);
    m_widgets_when_no_child.push_back(ui->checkBoxIsDone);
    m_widgets_when_no_child.push_back(ui->labelDNTListChild);

    this->updateView();

    QObject::connect(ui->pushButtonChangeToChild, SIGNAL(clicked()), this, SLOT(changeAxisWithButton()));
    QObject::connect(ui->pushButtonReturnToMaster, SIGNAL(clicked()), this, SLOT(changeAxisToMaster()));
    QObject::connect(ui->pushButtonAddNewAxis, SIGNAL(clicked()), this, SLOT(createNewChild()));
    QObject::connect(ui->pushButtonDeleteAxis, SIGNAL(clicked()), this, SLOT(removeCurrentAxis()));
    QObject::connect(ui->checkBoxIsDone, SIGNAL(clicked(bool)), this, SLOT(checkBoxClicked(bool)));
}

MainWindow::~MainWindow()
{
    m_root_axis->saveTree(m_path_of_the_project);
    delete ui;
}

void MainWindow::updateView(){
    ui->labelDescriptionOfTheAxis->setText(QString::fromStdString(m_current_axis->getDescription()));
    ui->labelShowPathAxis->setText(QString::fromStdString("Current path of axes : " + m_current_axis->getPathAxes()));
    if (m_current_axis->getChilds()->size() == 0){
        for (unsigned int i{0}; i < m_widgets_when_child.size(); i++)
            m_widgets_when_child[i]->hide();
        for (unsigned int i{0}; i < m_widgets_when_no_child.size(); i++)
            m_widgets_when_no_child[i]->show();
        ui->labelPercentSubDoneOrIsDone->setText("Is done : ");
        ui->labelDNTListChild->setText("");
        ui->checkBoxIsDone->setChecked(m_current_axis->getIsDone());
        this->resize(622, 250);
    }
    else{
        for (unsigned int i{0}; i < m_widgets_when_child.size(); i++)
            m_widgets_when_child[i]->show();
        for (unsigned int i{0}; i < m_widgets_when_no_child.size(); i++)
            m_widgets_when_no_child[i]->hide();
        ui->labelPercentSubDoneOrIsDone->setText("Percent of sub-axes done :");
        ui->labelDNTListChild->setText("List of sub Axes :");

        ui->comboBox->clear();
        for (auto &child : *m_current_axis->getChilds()){
            ui->comboBox->addItem(QString::fromStdString(child->getName()));
        }
        this->resize(622, 318);
        ui->progressBar->setValue(m_current_axis->getPercentDone());
    }
    if (m_current_axis == m_root_axis){
        ui->pushButtonReturnToMaster->hide();
    }
    else {
        ui->pushButtonReturnToMaster->show();
    }

}

void MainWindow::changeAxisWithButton(){
    std::string name_new_axis{ui->comboBox->currentText().toStdString()};
    AxisData* new_axis {m_current_axis->foundChild(name_new_axis)};
    if (new_axis != nullptr){
        m_current_axis = new_axis;
        this->updateView();
    }
}

void MainWindow::changeAxisToMaster(){
    AxisData* new_axis {m_current_axis->getParent()};
    if (new_axis != nullptr){
        m_current_axis = new_axis;
        this->updateView();
    }
}

void MainWindow::checkBoxClicked(bool state){
    m_current_axis->setIsDone(state);
}

void MainWindow::createNewChild(){
    std::string name = QInputDialog::getText(this, tr("Choose a name for the new axis"), tr("Choose a name for the axis : ")).toStdString();
    std::string desc = QInputDialog::getMultiLineText(this, tr("Choose a description for the new axis"), tr("Choose a descrption for the axis : ")).toStdString();
    if ((name != "") && (desc != "")){
        m_current_axis = new AxisData(name, desc, m_current_axis);
        this->updateView();
        std::string message {"The axis \"" + name + "\" was created"};
        QMessageBox::information(this, tr("Operation completed successfully"), QString::fromStdString(message));

    }
    else {
        QMessageBox::warning(this, tr("Operation failed"), tr("The axis wasn't created because the name or the description is empty"));
    }

}

void MainWindow::removeCurrentAxis(){
    std::string message{"Are you sure that you want to delete " + m_current_axis->getName()};
    int answer {QMessageBox::question(this, tr("Delete axis ?"), QString::fromStdString(message))};
    if (answer == QMessageBox::Yes){
        AxisData *next_current_axis = m_current_axis->getParent();
        next_current_axis->deleteChild(m_current_axis->getName());
        m_current_axis = next_current_axis;
    }
    this->updateView();
}
