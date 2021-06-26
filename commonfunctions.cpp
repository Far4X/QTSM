#include "commonfunctions.h"
#include <fstream>
#include <string>
#include <iostream>

const char *getHomeDir(){
    const char *home_dir;

    if ((home_dir = getenv("HOME")) == nullptr){
        throw "Impossible to found the home directory, with getenv('HOME')";
    }

    return home_dir;
}

const std::string getDisclaimerMessage(){
    return "#List of QTSM projects. This is just the list of all the projects. DO NOT TOUCH (Except if you are Far4X).";
}

const std::string getListPath(){
    return std::string(std::string(getHomeDir()) + "/Documents/.QTSM/list.pts");
}

std::map<std::string, std::string> getDictFic(){
    std::map<std::string, std::string> dict;

    std::ifstream flux_list_fics(getListPath());
    if(flux_list_fics){

        std::string line_fic;
        while(getline(flux_list_fics, line_fic)){

            if (line_fic.find("PROJECT") != std::string::npos){
                bool is_the_path = false;
                std::string name_project, path_project;

                for (unsigned long cnt(line_fic.find("PROJECT") + 8); cnt<=line_fic.size(); cnt++) {

                    if(line_fic[cnt] == '|'){
                        is_the_path = true;
                        std::cout << name_project << "OK" << std::endl;
                    }

                    else {
                        if (is_the_path){
                            path_project += line_fic[cnt];
                        }
                        else{
                            name_project += line_fic[cnt];
                        }
                    }
                }
                dict[name_project] = path_project;
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

        std::ofstream flux_create_list_fic(getListPath());
        flux_create_list_fic << getDisclaimerMessage() << std::endl;
    }
    for(auto &item : dict){
        std::cout << item.first << " : " << item.second << std::endl;
    }

    return dict;
}


