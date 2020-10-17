#ifndef SENSITIVESCHEMA_H
#define SENSITIVESCHEMA_H

#include <QObject>
#include <QList>
#include "uitls/interface.h"
#include "model/satdata.h"
#include "uitls/operationfield.h"

/*======================================

  档位设置模式 ： DisplaySchema
  左短按：切换档位
  左长按：切换档位
  右短按：切换档位
  右长按：切换档位
  进入时：+标记设真
  离开时：无操作

 ======================================*/
class GearSchema : public QObject , public AbstractSchema
{
    Q_OBJECT
public:
    GearSchema(QObject *parent = 0);
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
    QList<SatData::GearEnum> mList;
    int mIndex;
    SatData* mSatData;
};

#endif // SENSITIVESCHEMA_H
