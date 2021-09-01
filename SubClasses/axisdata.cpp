#include "axisdata.h"
#include "commonfunctions.h"
#include <iostream>
#include <fstream>

AxisData::AxisData(std::string def_of_this, AxisData *master){
    char current_char;
    int nb_of_braces = 0;
    m_parent = master;

    std::string current_param, value_of_current_param;
    bool equal_passed = false, can_be_ended = true;
    for (unsigned int i = 0; i < unsigned(int(def_of_this.size())); i++){
        current_char = def_of_this[i];
        if (equal_passed){
            if ((current_char == ',') && can_be_ended && nb_of_braces == 0){
                equal_passed = false;
                if (current_param == "name"){
                    m_name = value_of_current_param;
                }

                else if (current_param == "is_done"){
                    value_of_current_param == "true" ? m_is_done = true : m_is_done = false;
                    std::cout << m_name << " : matched param  : " << current_param << "; value : " << value_of_current_param << std::endl;

                }

                else if (current_param == "desc"){
                    replaceWord(value_of_current_param, "\\e", " ");
                    replaceWord(value_of_current_param, "\\n", "\n");
                    m_desc = value_of_current_param;
                    std::cout << m_name << " : matched param  : " << current_param << "; value : " << value_of_current_param << std::endl;
                }
                else if (current_param == "type"){
                    if (value_of_current_param != "RootAxisData"){
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
                                        if (type_of_child == "AxisData"){
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

AxisData::AxisData(std::string name, std::string &desc, AxisData *parent){
    m_name = name;
    m_desc = desc;
    m_parent = parent;
    m_is_done = false;
    m_childs = {};
    m_parent->appendChild(this);
}


AxisData::AxisData(){
    //Used to init the root
}

AxisData::~AxisData(){
    for (auto& child : m_childs){
        delete child;
    }
}

void AxisData::rename(std::string &new_name){
    if (!(m_parent->haveAChildNamed(new_name)))
        m_name = new_name;
    else
        throw "There is already a child named " + new_name;
}

void AxisData::appendChild(AxisData *new_child){
    m_childs.push_back(new_child);
}

void AxisData::deleteChild(std::string name){
    for(unsigned int i{0}; i < m_childs.size(); i++){
        if (m_childs[i]->getName() == name){
            AxisData *axis_to_delete = m_childs[i];
            m_childs.erase(m_childs.begin() + i);
            delete axis_to_delete;
        }
    }

}

void AxisData::setDescription(std::string& new_desc){
    m_desc = new_desc;
}

bool AxisData::haveAChildNamed(std::string name_to_check){
    for (auto &child : m_childs){
        if (child->getName() == name_to_check)
            return true;
    }
    return false;
}

AxisData *AxisData::getParent(){
    return m_parent;
}

std::string AxisData::getPathAxes(){
    return m_parent->getPathAxes() + "/" + m_name;
}

std::string AxisData::getDescription(){
    return m_desc;
}

std::string AxisData::getName(){
    return m_name;
}

std::vector<AxisData*>* AxisData::getChilds(){
    return &m_childs;
}


AxisData* AxisData::foundChild(std::string &name){
    for(auto &child : m_childs){
        if (child->getName() == name){
            return child;
        }
    }
    return nullptr;
}

std::string AxisData::getTree(){
    std::string branch_of_this{"\t" + m_name};
    for(unsigned int i{0}; i < (m_childs.size()); i++){
        branch_of_this += "\n\t";
        branch_of_this += m_childs[i]->getTree();
    }
    return  branch_of_this;
}

std::string AxisData::getDefinition(){
    replaceWord(m_desc, " ", "\\e");
    replaceWord(m_desc, "\n", "\\n");
    std::string definition{"type = \"" + this->getType() + "\", name = \"" + m_name + "\", desc = \"" + m_desc + "\", is_done = \"" + (m_is_done ? "true" : "false") + "\""};
    definition += ", childs = {";
    for (unsigned int i{0}; i < m_childs.size(); i++){
          definition += m_childs[i]->getDefinition();
    }
    definition += "};";
    replaceWord(m_desc, "\\e", " ");
    replaceWord(m_desc, "\\n", "\n");
    return definition;
}

std::string AxisData::getType(){
    return "AxisData";
}

int AxisData::getPercentDone(){
    int percent{0};
    if (m_childs.size() == 0){
        m_is_done ? percent = 100 : percent = 0;
    }
    else {
        for (auto &child : m_childs){
            percent += child->getPercentDone();
        }
        percent /= m_childs.size();
    }
    if (percent == 100)
        m_is_done = true;
    else
        m_is_done = false;
    return percent;
}

bool AxisData::getIsDone(){
    return m_is_done;
}

void AxisData::setIsDone(bool is_done){
    m_is_done = is_done;
}
