#include "rootaxisdata.h"
#include <fstream>

#include <iostream>

RootAxisData::RootAxisData(std::string& path){
    std::cout << "Path received : " << path << std::endl;
    std::ifstream input_flux(path);
    if (input_flux){
        char current_char;
        input_flux >> current_char;
        std::string def_of_this;
        int nb_of_braces = 0;
        while (((current_char != '}' && current_char != ';') || nb_of_braces != 0) && current_char != EOF){
            if (current_char == '{')
                nb_of_braces++;
            else if (current_char == '}')
                nb_of_braces--;

            def_of_this += current_char;
            input_flux >> current_char;

        }
        AxisData(def_of_this, nullptr);
    }
    else {
        throw ("Impossible to open " + path);
    }
}

RootAxisData::~RootAxisData(){

}

AxisData *RootAxisData::getParent(){
    return nullptr;
}

std::string RootAxisData::getPathAxes(){
    return this->getName();
}


std::string RootAxisData::getTree(){
    std::cout << "ok" << std::endl;
    std::string branch_of_this{this->getName()};
    std::cout << branch_of_this << std::endl;
    for(unsigned int i{0}; i < (this->getChilds()->size()); i++){
        branch_of_this += this->getChilds()->operator[](i)->getTree();
        branch_of_this += "\n";
    }
    std::cout << branch_of_this << std::endl;
    return branch_of_this;
}
