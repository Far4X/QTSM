#include "mainwindow.h"
#include "chooseaproject.h"
#include <QApplication>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sys/stat.h>

std::map<std::string, std::string> recoveryFic();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChooseAProject Tw;

    std::map<std::string, std::string> holder(recoveryFic()), *dict_projects=&holder;

    for(auto &item : *dict_projects){
        Tw.addElemInList(item.first);
    }

    Tw.show();

    return a.exec();
}



std::map<std::string, std::string> recoveryFic(){

    const char *home_dir;
    std::map<std::string, std::string> dict_projects;

    if ((home_dir = getenv("HOME")) == nullptr){
        throw "Impossible to found the home directory, with getenv('HOME')";
    }

    std::ifstream flux_list_fics(std::string(home_dir) + "/Documents/.QTSM/list.pts");
    if(flux_list_fics){

        std::string line_fic;

        while(getline(flux_list_fics, line_fic)){
            if (line_fic.find("PROJECT_NAME") != std::string::npos){
                bool is_the_path = false;
                std::string name_project;
                for (unsigned long cnt(line_fic.find("PROJECT_NAME") + 13); cnt<=line_fic.size(); cnt++) {
                    if(line_fic[cnt] == '|'){
                        is_the_path = true;
                        std::cout << name_project << "OK" << std::endl;
                    }
                    else {
                        if (is_the_path){
                           dict_projects[name_project] += line_fic[cnt];
                        }
                        else{
                            name_project += line_fic[cnt];
                        }
                    }


                }
            }
        }

    }
    else{

        std::string cmd("mkdir ~/Documents/.QTSM/");
        system(cmd.c_str());
        cmd = "touch ~/Documents/.QTSM/list.pts";
        system(cmd.c_str());
        cmd = "chmod 777 ~/Documents/.QTSM/list.pts";
        system(cmd.c_str());

        std::ofstream flux_create_list_fic(std::string(home_dir) + "/Documents/.QTSM/list.pts");
        flux_create_list_fic << "#List of QTSM projects. This is just the list of all the projects. DO NOT TOUCH (Except if you are Far4X)." << std::endl;
    }
    for(auto &item : dict_projects){
        std::cout << item.first << " : " << item.second << std::endl;
    }
    return (dict_projects);
}
