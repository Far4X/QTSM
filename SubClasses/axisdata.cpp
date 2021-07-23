#include "axisdata.h"

AxisData::AxisData(std::ifstream &input_flux, int position){

}

AxisData::AxisData(){
    //Used to init the root
}

AxisData::~AxisData(){

}

AxisData *AxisData::getParent(){
    return m_parent;
}

std::string AxisData::getPathAxes(){
    return getParent()->getPathAxes() + m_name;
}

std::string AxisData::getName(){
    return m_name;
}
