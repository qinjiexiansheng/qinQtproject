#ifndef CORRECTSCHEMA_H
#define CORRECTSCHEMA_H

#include <QObject>
#include "uitls/interface.h"
#include "model/satdata.h"
#include "uitls/operationfield.h"

/*======================================

  修正模式 ： CorrectSchema
  左短按：打档
  左长按：打档
  右短按：打开修正窗口
  右长按：打开修正窗口
  进入时：+标记设真
  离开时：无操作

 ======================================*/
class CorrectSchema : public QObject , public AbstractSchema
{
    Q_OBJECT
public:
    CorrectSchema(QObject *parent = 0);
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
};

#endif // CORRECTSCHEMA_H
