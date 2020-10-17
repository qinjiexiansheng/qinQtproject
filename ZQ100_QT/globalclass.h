#ifndef GLOBALCLASS_H
#define GLOBALCLASS_H

#include <QApplication>
#include "adjust/tabdialog.h"
#include "adjust/standardparamsetting.h"

class globalClass
{
public:
     globalClass();
    ~globalClass();

    // fpgaInterface
   static void setFpgaInterface(fpgaInterface *fpgaInterface);
   static fpgaInterface * getFpgaInterface();

   // Standardparamsetting
   static void setStandardparam(Standardparamsetting *standardparam);
   static Standardparamsetting* getStandardparam();

   // TabDialog
   static void setTabDialog(TabDialog *tabDialog);
   static TabDialog* getTabDialog();

private:
    static fpgaInterface* g_fpgaInterface;
    static Standardparamsetting* g_Standardparamsetting;
    static TabDialog* g_TabDialog;//标定窗口
};

#endif // GLOBALCLASS_H
