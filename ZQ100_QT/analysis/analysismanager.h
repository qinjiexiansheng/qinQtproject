#ifndef ANALYSISMANAGER_H
#define ANALYSISMANAGER_H

#include "globalparam.h"
#include "spot/spot.h"
#include "area/area.h"
#include "line/line.h"

class AnalysisManager
{
public:
    AnalysisManager(QWidget *parent);

    Spot* addSpot(/*int id*/);
    Area* addArea(/*int id*/);
    Line* addLine();

    void removeSpot(int id);
    void removeArea(int id);
    void removeLine();

private:
    //存储Spot指针
    QHash<QString, Spot *> spotMap;
    //存储Area指针
    QHash<QString, Area *> areaMap;
    //存储Line指针
    QHash<QString, Line *> lineMap;
    //存储父窗口指针
    QWidget *m_parent;
};

#endif // ANALYSISMANAGER_H
