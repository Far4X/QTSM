#ifndef AXISDATA_H
#define AXISDATA_H
#include <vector>
#include <string>
#include <fstream>

class AxisData
{
public:
    AxisData(std::string def_of_this, AxisData *master = nullptr);
    AxisData(std::string name, std::string &desc, AxisData *parent);
    AxisData();
    virtual ~AxisData();

    void setIsDone(bool is_done);
    void appendChild(AxisData* new_child);
    void deleteChild(std::string name);
    void setDescription(std::string &new_desc);
    int getPercentDone();
    bool getIsDone();
    bool haveAChildNamed(std::string name_to_check);
    std::vector<AxisData*>* getChilds();
    std::string getDefinition();
    std::string getDescription();
    AxisData *foundChild(std::string& name);

    virtual void rename(std::string &new_name);
    virtual std::string getTree();
    virtual AxisData *getParent();
    virtual std::string getPathAxes();
    virtual std::string getType();

    std::string getName();

protected :
    bool m_is_done;
    AxisData* m_parent;
    std::vector<AxisData*> m_childs;
    std::string m_name;
    std::string m_desc;
};

#endif // AXISDATA_H
