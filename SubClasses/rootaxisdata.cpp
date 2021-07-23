#include "rootaxisdata.h"
#include <fstream>

#include <iostream>

RootAxisData::RootAxisData(std::string& path){
    std::cout << "Path received : " << path << std::endl;
    std::ifstream input_flux(path);
    if (input_flux){
        AxisData(input_flux, int(input_flux.tellg()));
    }
    else {
        throw "Impossible to open " + path;
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
