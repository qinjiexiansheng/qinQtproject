#include "globalclass.h"

fpgaInterface* globalClass::g_fpgaInterface = NULL;
Standardparamsetting* globalClass::g_Standardparamsetting = NULL;
TabDialog* globalClass::g_TabDialog = NULL;

globalClass::globalClass()
{

}

 void globalClass::setFpgaInterface(fpgaInterface *fpgaInterface)
{
    g_fpgaInterface = fpgaInterface;
}

 fpgaInterface* globalClass::getFpgaInterface()
{
    if(g_fpgaInterface == NULL)
        g_fpgaInterface = new fpgaInterface;

    return g_fpgaInterface;
}

 void globalClass::setStandardparam(Standardparamsetting *standardparam)
{
    g_Standardparamsetting = standardparam;
}

 Standardparamsetting* globalClass::getStandardparam()
{
    if(g_Standardparamsetting == NULL)
        g_Standardparamsetting = new Standardparamsetting;
    return g_Standardparamsetting;
}

void globalClass::setTabDialog(TabDialog *tabDialog)
{
    g_TabDialog = tabDialog;
}
TabDialog* globalClass::getTabDialog()
{
    if(g_TabDialog == NULL)
        g_TabDialog = new TabDialog;
    return g_TabDialog;
}

