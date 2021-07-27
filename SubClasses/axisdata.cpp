#include "axisdata.h"
#include "commonfunctions.h"
#include <iostream>
#include <fstream>

AxisData::AxisData(std::ifstream &input_flux, int position){
    std::cout << position << std::endl;

    //input_flux.seekg(position);
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
    std::cout << def_of_this << std::endl;

    std::string current_param, value_of_current_param;
    bool equal_passed = false;
    for (unsigned int i = 0; i < unsigned(int(def_of_this.size())); i++){
        current_char = def_of_this[i];
        if (equal_passed){
            if (current_char == ','){
                equal_passed = false;
                if (current_param == "name")
                    m_name = value_of_current_param;
                else if (current_param == "desc"){
                    replaceWord(value_of_current_param, "_", " ");
                    m_desc = value_of_current_param;
                }
                current_param = "";
                value_of_current_param = "";
            }
        }
        else {
            if (current_char == '=')
                equal_passed = true;

        }
    }
}

AxisData::AxisData(std::string){

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
