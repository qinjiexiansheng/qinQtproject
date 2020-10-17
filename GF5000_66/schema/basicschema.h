#ifndef BASICSCHEMA_H
#define BASICSCHEMA_H

#include <QObject>
#include "uitls/interface.h"
#include "model/satdata.h"
#include "uitls/operationfield.h"
/*======================================

  基本模式 ： BasicSchema
  左短按：打档
  左长按：打档
  右短按：拍照/停止录像
  右长按：开始录像/停止录像
  进入时：+标记设假
  离开时：正在录像则停止录像

 ======================================*/
class BasicSchema : public QObject , public AbstractSchema
{
    Q_OBJECT
public:
    BasicSchema(QObject *parent = 0);
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

#endif // BASICSCHEMA_H
