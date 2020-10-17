#include "SatControl.h"
#include "operationfield.h"

SatControl* SatControl::_SatControl = NULL;


SatControl::SatControl(QObject *parent) : QObject(parent)
{

}

 SatControl* SatControl::initance()
{
    if(_SatControl == NULL){
        _SatControl = new SatControl();
    }

    return _SatControl;
}

void SatControl::doService(int nOpeStr,QString nParStr)
{
    if(nOpeStr == Effect_TempAd_Table){
        mTempADOpe->takeEffectADTable();
    }else if(nOpeStr == Update_TempAd_Table){
        mTempADOpe->updateADTable();
        mOtherOpe->loadModelData();    }
}
