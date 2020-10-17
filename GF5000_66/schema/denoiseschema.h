#ifndef DENOISESCHEMA_H
#define DENOISESCHEMA_H

#include <QObject>
#include <QList>
#include "uitls/interface.h"
#include "model/satdata.h"
#include "uitls/operationfield.h"

/*======================================

  降噪模式 ： DenoiseSchema
  左短按：切换降噪算法
  左长按：切换降噪算法
  右短按：切换降噪算法
  右长按：切换降噪算法
  进入时：+标记设真
  离开时：无操作

 ======================================*/
class DenoiseSchema : public QObject , public AbstractSchema
{
    Q_OBJECT
public:
    DenoiseSchema(QObject *parent = 0);
    QString name();
    QString imageNormal();
    QString imageFocus();
    QString imageLight();
    int doLeftShort();
    int doLeftLong();
    int doRightShort();
    int doRightLong();
    int doRightRelease();
    int entryMode();
    int leaveMode();
private:
    SatData* mSatData;
    int mIndex;
    QList<SatData::DenoiseEnum> mList;
};

#endif // DENOISESCHEMA_H
