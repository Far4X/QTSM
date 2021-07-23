#ifndef VIRTUALAXISDATA_H
#define VIRTUALAXISDATA_H
#include <vector>
#include <string>
#include <fstream>

class AxisData
{
public:
    AxisData(std::ifstream &input_flux, int position);
    AxisData();
    virtual ~AxisData();

    bool percentDone();
    void appendChild(AxisData new_child);
    void deleteChild();

    virtual AxisData *getParent();
    virtual std::string getPathAxes();

    std::string getName();

private:
    bool m_is_done;
    AxisData* m_parent;
    std::vector<AxisData> childs;
    std::string m_name;
    std::string m_desc;
};

#endif // AXISDATA_H
