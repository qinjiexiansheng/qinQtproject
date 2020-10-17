#include "analysismanager.h"

/**
 * @name    AnalysisManager(QWidget *parent)
 * @details 用于管理Spot/Area/Line测温工具
 * @param   parent  父窗口指针
 * @author  lee
 * @date    2018-12-20
**/
AnalysisManager::AnalysisManager(QWidget *parent)
    : m_parent(parent)
{
}

/**
 * @name    Spot * addSpot()
 * @details 往Spot列表中添加一个Spot。如果列表已存在该Spot指针，则直接返回该指针，否则新建一个Spot
 * @author  lee
 * @date    2018-12-20
**/
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

/**
 * @name    void removeSpot(int id)
 * @details 从Spot列表中指定id的Spot
 * @param   id  Spot的id
 * @author  lee
 * @date    2018-12-20
**/
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

/**
 * @name    Area * addArea()
 * @details 往Area列表中添加一个Area。如果列表已存在该Area指针，则直接返回该指针，否则新建一个Area
 * @author  lee
 * @date    2018-12-20
**/
Area * AnalysisManager::addArea(/*int id*/)
{
    int id = areaMap.count();

    foreach (Area *temp, areaMap) {
        if(temp->isHidden())
        {
            return temp;
        }
    }
    QString name = QString("Area%1").arg(areaMap.count());
    QHash<QString, Area *>::iterator i = areaMap.find(name);
    if(i == areaMap.end())
    {
        if(areaMap.count() < MAXAREANUM)
        {
            Area *area = new Area(m_parent, id);
            areaMap.insert(name, area);
            return area;
        }
        else
            return NULL;
    }
    else
    {
        return i.value();
    }
}

/**
 * @name    void removeArea(int id)
 * @details 从Area列表中指定id的Area
 * @param   id  Area的id
 * @author  lee
 * @date    2018-12-20
**/
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

/**
 * @name    Line * addLine()
 * @details 往Line列表中添加一个Line。如果列表已存在该Line指针，则直接返回该指针，否则新建一个Line
 * @author  lee
 * @date    2018-12-20
**/
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

/**
 * @name    void removeLine()
 * @details 从Line列表中移除Line
 * @author  lee
 * @date    2018-12-20
**/
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


