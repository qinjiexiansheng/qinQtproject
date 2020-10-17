#include "initfpga.h"
#include "globalparam.h"
initFpga::initFpga()
{
      qDebug("initFpga::initFpga()");

    _FpgaInterface = new fpgaInterface;
    _Standardparamsetting = new Standardparamsetting(GlobalParam::getParentWidget());
    _tabDialog = new TabDialog(GlobalParam::getParentWidget());
    _tabDialog->hide();

    globalClass::setFpgaInterface(_FpgaInterface);
    globalClass::setStandardparam(_Standardparamsetting);
    globalClass::setTabDialog(_tabDialog);

    globalClass::getStandardparam()->loadIRParameter();

    getVsk  = globalClass::getStandardparam()->getStandardparamsVsk();
    getFid  = globalClass::getStandardparam()->getStandardparamsFid();
    getGain = globalClass::getStandardparam()->getStandardparamsGain();

    qDebug("getVsk = %d",getVsk);
    qDebug("getFid = %d",getFid);
    qDebug("getGain = %d",getGain);


    globalClass::getFpgaInterface()->fpgaGskFidSet(getVsk, getFid);
    globalClass::getFpgaInterface()->fpgaGainSet(getGain);

    globalClass::getFpgaInterface()->fpgaPointPositionSet(0, 11, 22);
    globalClass::getFpgaInterface()->fpgaLinePositionSet(55);
    globalClass::getFpgaInterface()->fpgaAreaPositionSet(1, 11, 22, 33, 44);


}
initFpga::~initFpga()
{

}

