#ifndef VIRTUALAXISDATA_H
#define VIRTUALAXISDATA_H
#include <vector>
#include <string>
#include <fstream>

class AxisData
{
public:
    AxisData(std::string def_of_this, AxisData *master = nullptr);
    AxisData();
    virtual ~AxisData();

    bool percentDone();
    void appendChild(AxisData* new_child);
    void deleteChild();
    std::vector<AxisData*>* getChilds();

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
