#include "mainwindow.h"
#include "chooseaproject.h"
#include "commonfunctions.h"
#include <QApplication>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>


std::map<std::string, std::string> recoveryFic();

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    ChooseAProject FirstWindow;

    std::map<std::string, std::string> holder(getDictFic()), *dict_projects=&holder;

    for(auto &item : *dict_projects){
        FirstWindow.addElemInList(item.first);
    }

    FirstWindow.show();

    return a.exec();
}
