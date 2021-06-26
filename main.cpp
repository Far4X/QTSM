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
    ChooseAProject Tw;

    std::map<std::string, std::string> holder(getDictFic()), *dict_projects=&holder;

    for(auto &item : *dict_projects){
        Tw.addElemInList(item.first);
    }

    Tw.show();

    return a.exec();
}
