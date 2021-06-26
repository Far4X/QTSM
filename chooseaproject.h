#ifndef CHOOSEAPROJECT_H
#define CHOOSEAPROJECT_H

#include <QWidget>
#include <string>

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

private:
    Ui::ChooseAProject *ui;
};

#endif // CHOOSEAPROJECT_H
