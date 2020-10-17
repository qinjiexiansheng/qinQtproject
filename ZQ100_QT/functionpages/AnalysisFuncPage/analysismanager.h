#ifndef ANALYSISMANAGER_H
#define ANALYSISMANAGER_H

#include <QHash>
#include <QWidget>
#include "spot.h"
#include "area.h"
#include "line.h"

class AnalysisManager
{
public:
    AnalysisManager(QWidget *parent);

    Spot* addSpot(int id);
    Area* addArea(int id);
    Line* addLine();

    void removeSpot(int id);
    void removeArea(int id);
    void removeLine();

private:
    QHash<QString, Spot *> spotMap;
    QHash<QString, Area *> areaMap;
    QHash<QString, Line *> lineMap;
    QWidget *m_parent;
};

#endif // ANALYSISMANAGER_H
