#include "analysismanager.h"
#include <QPushButton>
#include <QDebug>

AnalysisManager::AnalysisManager(QWidget *parent)
    : m_parent(parent)
{
}

Spot * AnalysisManager::addSpot(/*int id*/)
{
    int id = spotMap.count();

    foreach (Spot *temp, spotMap) {
        if(temp->isHidden())
        {
            return temp;
        }
    }

    QString name = QString("Spot%1").arg(spotMap.count());
    QHash<QString, Spot *>::iterator i = spotMap.find(name);
    if(i == spotMap.end())
    {
        if(spotMap.count() < MAXSPOTNUM)
        {
            Spot *spot = new Spot(m_parent, id);
            spotMap.insert(name, spot);
            return spot;
        }
        else
            return NULL;
    }
    else
    {
        return i.value();
    }
}

void AnalysisManager::removeSpot(int id)
{
    QString name = QString("Spot%1").arg(id);
    QHash<QString, Spot *>::iterator i = spotMap.find(name);
    if(i != spotMap.end())
    {
        i.value()->close();
        spotMap.remove(i.key());
    }
}

Area * AnalysisManager::addArea(int id)
{
    QString name = QString("Area%1").arg(id);
    QHash<QString, Area *>::iterator i = areaMap.find(name);
    if(i == areaMap.end())
    {
        Area *area = new Area(m_parent, id);
        QHash<QString, Area *>::iterator j = areaMap.insert(name, area);
        return area;
    }
    else
    {
        return i.value();
    }
}

void AnalysisManager::removeArea(int id)
{
    QString name = QString("Area%1").arg(id);
    QHash<QString, Area *>::iterator i = areaMap.find(name);
    if(i != areaMap.end())
    {
        i.value()->close();
        areaMap.remove(i.key());
    }
}

Line * AnalysisManager::addLine()
{
    QString name = QString("Line");
    QHash<QString, Line *>::iterator i = lineMap.find(name);
    if(i == lineMap.end())
    {
        Line *line = new Line(m_parent);
        lineMap.insert(name, line);
        return line;
    }
    else
    {
        return i.value();
    }
}

void AnalysisManager::removeLine()
{
    QString name = QString("Line");
    QHash<QString, Line *>::iterator i = lineMap.find(name);
    if(i != lineMap.end())
    {
        i.value()->close();
        lineMap.remove(i.key());
    }
}


