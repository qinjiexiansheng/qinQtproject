#ifndef IMAGEFREESCHEMA_H
#define IMAGEFREESCHEMA_H

#include <QObject>
#include "uitls/interface.h"
#include "model/satdata.h"
#include "uitls/operationfield.h"

/*======================================

  图像冻结模式 ： ImageFreeSchema
  左短按：打档(解冻状态)/拍照(冻结状态)
  左长按：同上
  右短按：冻结/解冻
  右长按：同上
  进入时：+标记设真
  离开时：解冻(冻结状态)

 ======================================*/
class ImageFreeSchema : public QObject , public AbstractSchema
{
    Q_OBJECT
public:
    ImageFreeSchema(QObject *parent = 0);
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

#endif // IMAGEFREESCHEMA_H
