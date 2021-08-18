#include "commonfunctions.h"
#include <fstream>
#include <string>
#include <iostream>


//The following function returns the directory of the current user (Works on linux, idk for Windows)

const char *getHomeDir(){
    const char *home_dir;

    if ((home_dir = getenv("HOME")) == nullptr){
        throw "Impossible to found the home directory, with getenv('HOME')";
    }

    return home_dir;
}


//The following function just returns the message at the start of the file "list.pts" (pts stands for paths)

const std::string getDisclaimerMessage(){
    return "#List of QTSM projects. This is just the list of all the projects. DO NOT TOUCH (Except if you are Far4X).";
}


//The following function returns the path of the file where is the list of all the projects and their paths

const std::string getListPath(){
    return std::string(std::string(getHomeDir()) + "/Documents/.QTSM/list.pts");
}

std::string transformPathToRootAxisDesc(std::string& path){
    std::cout << "Path received : " << path << std::endl;
    std::ifstream input_flux(path);
    if (input_flux){
        char current_char;
        input_flux >> current_char;
        std::string def_of_root_axis;
        int nb_of_braces = 0;
        while (((current_char != '}' && current_char != ';') || nb_of_braces != 0) && current_char != EOF){
            if (current_char == '{')
                nb_of_braces++;
            else if (current_char == '}')
                nb_of_braces--;

            def_of_root_axis += current_char;
            input_flux >> current_char;

        }
        return def_of_root_axis;
    }
   else {
        throw ("Impossible to open " + path);
   }
}

//The following function returns a map with the name of the project as the first item and the path as the second

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


//The next function rewrite the folder with a new/modified dict

void rewriteFile(const std::map<std::string, std::string> &dict){
    std::ofstream fileFlux(getListPath());

    fileFlux << getDisclaimerMessage() << '\n' << std::endl;

    for(auto &item : dict){
        std::string path(item.second);
        if (path != ""){
            if (path[path.size()-1] != 'm'){
                fileFlux << "PROJECT:" << item.first << "|" << path.erase(path.size()-1) << '\n';
            }
            else{
                fileFlux << "PROJECT:" << item.first << "|" << path << '\n';
            }
            std::flush(fileFlux);
        }
        else {
            throw "Impossible to found the path of the " + item.first + " project";
        }
    }

    fileFlux << '\n' <<"Writing completed" << std::endl;
}


void replaceWord(std::string &original, const std::string &to_find, const std::string &to_replace){
    unsigned int i = unsigned(int(original.find(to_find)));
    while (i != unsigned(int(std::string::npos))){
        original.replace(i, to_find.size(), to_replace);
        i = unsigned(int(original.find(to_find)));
    }
}
