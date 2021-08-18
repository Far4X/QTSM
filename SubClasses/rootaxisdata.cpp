#include "rootaxisdata.h"
#include "commonfunctions.h"
#include <fstream>

#include <iostream>

RootAxisData::RootAxisData(std::string& path) : AxisData(transformPathToRootAxisDesc(path), nullptr){

}

RootAxisData::~RootAxisData(){

}

AxisData *RootAxisData::getParent(){
    return nullptr;
}

std::string RootAxisData::getPathAxes(){
    return m_name;
}


std::string RootAxisData::getTree(){
    std::string branch_of_this{m_name};
    for(unsigned int i{0}; i < (m_childs.size()); i++){
        branch_of_this += "\n";
        branch_of_this += m_childs[i]->getTree();
    }
    return branch_of_this;
}

std::string RootAxisData::getType(){
    return "RootAxisData";
}
