#include "axisdata.h"
#include "commonfunctions.h"
#include <iostream>
#include <fstream>

AxisData::AxisData(std::string def_of_this, AxisData *master){

    if (master == nullptr)
        std::cout << "Def of this : " <<  def_of_this << std::endl;
    else
        std::cout << "Def of this : " <<  def_of_this << " Master : " << master->getName() << std::endl;

    char current_char;
    int nb_of_braces = 0;

    std::string current_param, value_of_current_param;
    bool equal_passed = false, can_be_ended = true;
    for (unsigned int i = 0; i < unsigned(int(def_of_this.size())); i++){
        current_char = def_of_this[i];
        if (equal_passed){
            if (current_char == ',' && can_be_ended && nb_of_braces == 0){
                equal_passed = false;
                if (current_param == "name"){
                    std::cout << "Name of : " << m_name << " is now : " << value_of_current_param << std::endl;
                    m_name = value_of_current_param;
                }


                else if (current_param == "is_done")
                    value_of_current_param == "true" ? m_is_done = true : m_is_done = false;

                else if (current_param == "desc"){
                    replaceWord(value_of_current_param, "_", " ");
                    m_desc = value_of_current_param;
                }
                else if (current_param == "type"){
                    if (value_of_current_param != "RootAxis"){
                        throw "Type diffrent of RootAxis";
                    }
                }

                else {
                    std::cout << "Unknow parm : '" << current_param << "', value : " << value_of_current_param << std::endl;
                }

                current_param = "";
                value_of_current_param = "";
            }
            else {
                if (current_char == '{' || current_char == '}'){
                    value_of_current_param += current_char;
                    if (current_char == '{')
                        nb_of_braces++;
                    else {
                        nb_of_braces--;
                        if (current_param == "childs" && nb_of_braces == 0){
                            std::cout << "\n\tChilds : " << value_of_current_param << "\n" << std::endl;

                            bool type_passed = false;
                            int nb_of_braces_in_child = 0;
                            std::string desc_of_current_child, type_of_child;

                            for (unsigned int j = 0; j < value_of_current_param.size(); j++){
                                current_char = value_of_current_param[j];
                                if (type_passed){
                                    if (current_char != ';' || nb_of_braces_in_child != 1){
                                        desc_of_current_child += current_char;
                                        if (current_char == '{')
                                            nb_of_braces_in_child ++;
                                        else if (current_char == '}')
                                            nb_of_braces_in_child --;
                                    }
                                    else {
                                        type_passed = false;
                                        std::cout << "New child : " << desc_of_current_child << "\nType : " << type_of_child <<std::endl;
                                        if (type_of_child == "BasicAxis"){
                                            m_childs.push_back(new AxisData(desc_of_current_child, this));
                                        }
                                        desc_of_current_child = "";
                                        type_of_child = "";
                                    }

                                }

                                else {
                                    if (current_char != ' ' && current_char != '=' && current_char != '\"' && current_char != ',' && current_char != '{')
                                        type_of_child += current_char;
                                    else if (current_char == '='){
                                        if (type_of_child == "type"){
                                            type_of_child = "";
                                        }
                                    }
                                    else if (current_char == ','){
                                        type_passed = true;
                                    }
                                    else if (current_char == '{')
                                        nb_of_braces_in_child++;
                                }
                            }
                        }
                    }

                }
                else if (current_char != '\"' && current_char != ' ')
                    value_of_current_param += current_char;
                else if (current_char == '\"'){
                    if (current_param != "childs")
                        can_be_ended = !can_be_ended;
                    else
                        value_of_current_param += '\"';
                }
            }
        }
        else {
            if (current_char == '=')
                equal_passed = true;

            else if (current_char != ' ')
                current_param += current_char;

        }
    }
    if (master == this)
        master->appendChild(this);
}

AxisData::AxisData(){
    //Used to init the root
}

AxisData::~AxisData(){

}

void AxisData::appendChild(AxisData *new_child){
    m_childs.push_back(new_child);
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

std::vector<AxisData*>* AxisData::getChilds(){
    return &m_childs;
}

std::string AxisData::getTree(){
    std::string branch_of_this{"\t" + m_name};
    for(unsigned int i{0}; i < (m_childs.size()); i++){
        branch_of_this += "\n\t";
        branch_of_this += m_childs[i]->getTree();
    }
    return  branch_of_this;
}

std::string AxisData::getType(){
    return "AxisData";
}
