#ifndef INFRAREDSCHEMA_H
#define INFRAREDSCHEMA_H

#include <QObject>
#include <QList>
#include "uitls/interface.h"
#include "model/satdata.h"
#include "uitls/operationfield.h"
/*======================================

  红外图像选择模式 ： InfraredSchema
  左短按：切换红外图像显示模式
  左长按：同上
  右短按：同上
  右长按：同上
  进入时：+标记设真
  离开时：无操作

 ======================================*/
class InfraredSchema : public QObject , public AbstractSchema
{
    Q_OBJECT
public:
    InfraredSchema(QObject *parent = 0);
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
    QList<SatData::InfraredEnum> mList;
    int mIndex;
    SatData* mSatData;


};

#endif // INFRAREDSCHEMA_H
