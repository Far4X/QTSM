#ifndef ROOTAXISDATA_H
#define ROOTAXISDATA_H
#include "axisdata.h"
#include <string>

class RootAxisData : public AxisData
{
public:
    RootAxisData(std::string &path);
    virtual ~RootAxisData();
    void saveTree(std::string &path);
    virtual void rename(std::string &new_name);
    virtual AxisData *getParent();
    virtual std::string getPathAxes();
    virtual std::string getTree();
    virtual std::string getType();

};

#endif // ROOTAXISDATA_H
