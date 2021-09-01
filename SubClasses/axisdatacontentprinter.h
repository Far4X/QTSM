#ifndef AXISDATACONTENTPRINTER_H
#define AXISDATACONTENTPRINTER_H

#include <QWidget>
#include "axisdata.h"

namespace Ui {
class AxisDataContentPrinter;
}

class AxisDataContentPrinter : public QWidget
{
    Q_OBJECT

public:
    explicit AxisDataContentPrinter(AxisData *content_to_print, QWidget *parent = nullptr);
    ~AxisDataContentPrinter();

public slots :
    void renameAxisData();
    void redescribeAxisData();


private:
    Ui::AxisDataContentPrinter *ui;
    AxisData *m_content_to_print;
};

#endif // AXISDATACONTENTPRINTER_H
