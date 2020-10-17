#-------------------------------------------------
#
# Project created by QtCreator 2018-11-19T14:05:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZQ100_QT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += _SAT_XNJ_

if(contains(myPLATFORM,pc)){ # { must here
    message("compile for pc")
    DEFINES += PC
    DEFINES += SHOWTEMP
}

if(contains(myPLATFORM,arm)){ # { must here
    message("compile for arm")
    DEFINES += ARM
}

SOURCES += \
    analysis/area/area.cpp \
    analysis/area/areapropertywnd.cpp \
    analysis/line/line.cpp \
    analysis/spot/spot.cpp \
    analysis/spot/spotpropertywnd.cpp \
    analysis/analysisfuncpage.cpp \
    analysis/analysismanager.cpp \
    analysis/examplepage.cpp \
    basewidget/combobox.cpp \
    basewidget/dateeditor.cpp \
    basewidget/linedelegate.cpp \
    basewidget/menubutton.cpp \
    basewidget/optionslistwidget.cpp \
    basewidget/scrollarea.cpp \
    basewidget/slidearea.cpp \
    basewidget/slidewidget.cpp \
    basewidget/spinbox.cpp \
    basewidget/switchbutton.cpp \
    basewidget/titlebar.cpp \
    caltemp/calactmp.cpp \
    caltemp/fpgaInterface.cpp \
    caltemp/irinfo.cpp \
    caltemp/readcfgfile.cpp \
    caltemp/table.cpp \
    caltemp/tfpga.cpp \
    keyboard/keyboard.cpp \
    keyboard/littlewidget.cpp \
    keyboard/softkeyboard.cpp \
    setting/analysissettingpage/analysissettingpage.cpp \
    setting/analysissettingpage/comptemppage.cpp \
    setting/analysissettingpage/emisstablepage.cpp \
    setting/analysissettingpage/globalparampage.cpp \
    setting/analysissettingpage/temprangepage.cpp \
    setting/systemsettingpage/controlpage.cpp \
    setting/systemsettingpage/powermanagerpage.cpp \
    setting/systemsettingpage/systemsettingpage.cpp \
    setting/systemsettingpage/timesettingpage.cpp \
    setting/systemsettingpage/unitsettingpage.cpp \
    setting/systemsettingpage/updatepage.cpp \
    setting/systemsettingpage/wifimanagerpage.cpp \
    globalparam.cpp \
    main.cpp \
    tmainpage.cpp \
    utility/utility.cpp \
    utility/yuv2rgbconverter.cpp \
    basewidget/label.cpp \
    adjust/AskDialog.cpp \
    adjust/config.cpp \
    adjust/DigitKeyboard.cpp \
    adjust/globalparam.cpp \
    adjust/HexadecimalKeyboard.cpp \
    adjust/littlewidget.cpp \
    adjust/mainwindow.cpp \
    adjust/modifyadtablewidget.cpp \
    adjust/SatControl.cpp \
    adjust/satdata.cpp \
    adjust/sattabwidget.cpp \
    adjust/saveadwidget.cpp \
    adjust/serialnumberwidget.cpp \
    adjust/SetDateWidget.cpp \
    adjust/SetGearWidget.cpp \
    adjust/ShowAdTableWidget.cpp \
    adjust/spinbox.cpp \
    adjust/spinboxstandard.cpp \
    adjust/standard.cpp \
    adjust/standardparamsetting.cpp \
    adjust/tabdialog.cpp \
    adjust/tabpage.cpp \
    adjust/TabPageFive.cpp \
    adjust/tabpagefour.cpp \
    adjust/tabpageone.cpp \
    adjust/tabpagethree.cpp \
    adjust/tabpagetwo.cpp \
    adjust/TempADOperation.cpp \
    adjust/FileOpe.cpp




HEADERS  += \
    analysis/area/area.h \
    analysis/area/areapropertywnd.h \
    analysis/line/line.h \
    analysis/spot/spot.h \
    analysis/spot/spotpropertywnd.h \
    analysis/analysisfuncpage.h \
    analysis/analysismanager.h \
    analysis/examplepage.h \
    basewidget/combobox.h \
    basewidget/dateeditor.h \
    basewidget/linedelegate.h \
    basewidget/menubutton.h \
    basewidget/optionslistwidget.h \
    basewidget/scrollarea.h \
    basewidget/slidearea.h \
    basewidget/slidewidget.h \
    basewidget/spinbox.h \
    basewidget/switchbutton.h \
    basewidget/titlebar.h \
    caltemp/calactmp.h \
    caltemp/color_tables.h \
    caltemp/color_tables_hsl.h \
    caltemp/fpga_global.h \
    caltemp/fpgadefine.h \
    caltemp/fpgaInterface.h \
    caltemp/irinfo.h \
    caltemp/table.h \
    caltemp/tfpga.h \
    keyboard/interface.h \
    keyboard/keyboard.h \
    keyboard/littlewidget.h \
    keyboard/macrodefine.h \
    keyboard/softkeyboard.h \
    setting/analysissettingpage/analysissettingpage.h \
    setting/analysissettingpage/comptemppage.h \
    setting/analysissettingpage/emisstablepage.h \
    setting/analysissettingpage/globalparampage.h \
    setting/analysissettingpage/temprangepage.h \
    setting/systemsettingpage/controlpage.h \
    setting/systemsettingpage/powermanagerpage.h \
    setting/systemsettingpage/systemsettingpage.h \
    setting/systemsettingpage/timesettingpage.h \
    setting/systemsettingpage/unitsettingpage.h \
    setting/systemsettingpage/updatepage.h \
    setting/systemsettingpage/wifimanagerpage.h \
    globalheader.h \
    globalparam.h \
    tmainpage.h \
    utility/utility.h \
    utility/yuv2rgbconverter.h \
    basewidget/label.h \
    adjust/AskDialog.h \
    adjust/config.h \
    adjust/DigitKeyboard.h \
    adjust/HexadecimalKeyboard.h \
    adjust/littlewidget.h \
    adjust/modifyadtablewidget.h \
    adjust/operationfield.h \
    adjust/operationfile.h \
    adjust/SatControl.h \
    adjust/satdata.h \
    adjust/satdefine.h \
    adjust/sattabwidget.h \
    adjust/saveadwidget.h \
    adjust/serialnumberwidget.h \
    adjust/SetDateWidget.h \
    adjust/SetGearWidget.h \
    adjust/ShowAdTableWidget.h \
    adjust/spinboxstandard.h \
    adjust/standard.h \
    adjust/standardparamsetting.h \
    adjust/tabdialog.h \
    adjust/tabpage.h \
    adjust/TabPageFive.h \
    adjust/tabpagefour.h \
    adjust/tabpageone.h \
    adjust/tabpagethree.h \
    adjust/tabpagetwo.h \
    adjust/TempADOperation.h \
    adjust/interface.h \
    adjust/FileOpe.h




RESOURCES += \
    res.qrc

FORMS += \
    adjust/AskDialog.ui \
    adjust/DigitKeyboard.ui \
    adjust/HexadecimalKeyboard.ui \
    adjust/modifyadtablewidget.ui \
    adjust/SatControl.ui \
    adjust/saveadwidget.ui \
    adjust/serialnumberwidget.ui \
    adjust/SetDateWidget.ui \
    adjust/SetGearWidget.ui \
    adjust/ShowAdTableWidget.ui \
    adjust/TabPageFive.ui \
    adjust/tabpagefour.ui \
    adjust/tabpagethree.ui
