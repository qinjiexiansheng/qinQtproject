#ifndef DISPLAYSCHEMA_H
#define DISPLAYSCHEMA_H

#include <QObject>
#include "uitls/interface.h"
#include "model/satdata.h"
#include "uitls/operationfield.h"

/*======================================

  显示设置模式 ： DisplaySchema
  左短按：显示/关闭窗口信息显示
  左长按：显示/关闭窗口信息显示
  右短按：显示/关闭高低温点显示
  右长按：显示/关闭高低温点显示
  进入时：+标记设真
  离开时：无操作

 ======================================*/
class DisplaySchema : public QObject , public AbstractSchema
{
    Q_OBJECT
public:
    DisplaySchema(QObject *parent = 0);
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

#endif // DISPLAYSCHEMA_H
