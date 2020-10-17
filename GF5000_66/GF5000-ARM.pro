#-------------------------------------------------
#
# Project created by QtCreator 2018-04-02T14:53:41
#
#-------------------------------------------------

QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GF5000
TEMPLATE = app
#QTPLUGIN += qjpeg

SOURCES  += main.cpp\
    view/mainwindow.cpp \
    model/satdata.cpp \
    schema/basicschema.cpp \
    service/infraredmode.cpp \
    service/camera.cpp \
    service/imagedenoise.cpp \
    service/otherbus.cpp \
    schema/displayschema.cpp \
    schema/infraredschema.cpp \
    schema/denoiseschema.cpp \
    schema/imagefreeschema.cpp \
    schema/correctschema.cpp \
    view/solidbar.cpp \
    controller/keyscan.cpp \
    service/datarefresh.cpp \
    service/parameteradjust.cpp \
    view/tabpage.cpp \
    view/tabdialog.cpp \
    view/softkeyboard.cpp \
    view/smallwidget.cpp \
    view/setparamwidget.cpp \
    view/modifyadtablewidget.cpp \
    schema/gearschema.cpp \
    service/gearadjust.cpp \
    controller/satcontrol.cpp \
    uitls/fileope.cpp \
    view/littlewidget.cpp \
    view/userwidget.cpp \
	view/systemwidget.cpp \
    view/globalparamwidget.cpp \
    view/gearsetwidget.cpp \
    view/emissivitytablewidget.cpp \
    view/languagewidget.cpp \
    view/updateprogramwidget.cpp \
    view/datetimewidget.cpp \
    view/systemcontrolwidget.cpp \
    view/setunitwidget.cpp \
    view/powermanagewidget.cpp \
    view/shutterintervalwidget.cpp \
    view/autosavepicturewidget.cpp \
    view/picturebrowingwidget.cpp \
	controller/videodecode.cpp \
    view/videowidget.cpp
	

HEADERS  += view/mainwindow.h \
    model/satdata.h \
    lib/temp.h \
    schema/basicschema.h \
    service/infraredmode.h \
    service/camera.h \
    uitls/interface.h \
    service/imagedenoise.h \
    service/otherbus.h \
    schema/displayschema.h \
    schema/infraredschema.h \
    schema/denoiseschema.h \
    schema/imagefreeschema.h \
    schema/correctschema.h \
    view/solidbar.h \
    lib/tircolor.h \
    lib/client.h \
    lib/global.h \
    controller/keyscan.h \
    uitls/macrodefine.h \
    service/datarefresh.h \
    service/parameteradjust.h \
    view/tabpage.h \
    view/tabdialog.h \
    view/softkeyboard.h \
    view/smallwidget.h \
    view/setparamwidget.h \
    view/modifyadtablewidget.h \
    schema/gearschema.h \
    service/gearadjust.h \
    controller/satcontrol.h \
    uitls/fileope.h \
    uitls/operationfield.h \
    view/littlewidget.h \
    view/userwidget.h \
	view/systemwidget.h \
    view/globalparamwidget.h \
    view/gearsetwidget.h \
    view/emissivitytablewidget.h \
    view/languagewidget.h \
    view/updateprogramwidget.h \
    view/datetimewidget.h \
    view/systemcontrolwidget.h \
    view/setunitwidget.h \
    view/powermanagewidget.h \
    view/shutterintervalwidget.h \
    view/autosavepicturewidget.h \
	view/picturebrowingwidget.h \
	uitls/exifparam.h \
    controller/videodecode.h \
    lib/include/libavcodec/avcodec.h \
    lib/include/libavformat/avformat.h \
    lib/include/libavutil/avutil.h \
    lib/include/libavutil/mem.h \
    lib/include/libavutil/fifo.h \
    lib/include/libswscale/swscale.h \
    view/videowidget.h


INCLUDEPATH += $$PWD/lib/include
INCLUDEPATH += $$PWD/lib/x264-arm/lib


LIBS += -L$$PWD/lib/ -lclient -ltemp
LIBS += -L$$PWD/lib/lib-arm-tmp/ -lavcodec -lavformat -lswscale -lavdevice 
LIBS += -L$$PWD/lib/lib-arm-tmp/ -lpostproc -lswresample   -lavutil  -lavfilter  




RESOURCES +=
DEFINES += _SAT_ARM_
#DEFINES += _SAT_XNJ_
TRANSLATIONS += qzher_en.ts



