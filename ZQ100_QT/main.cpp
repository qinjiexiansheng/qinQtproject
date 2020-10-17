#include <QApplication>
#include "tmainpage.h"
//#include "setting/analysissettingpage/comptemppage.h"
//#include "keyboard/softkeyboard.h"

#include <QColorDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /***MediaPlayer***/
    //    QMediaPlayer* player = new QMediaPlayer;
    //    player->setMedia(QUrl::fromLocalFile("/home/osrc/lee/D300_QT/pics/movie.mp4"));
    //    QVideoWidget *videoWidget = new QVideoWidget(this);
    //    videoWidget->setMaximumSize(320, 240);
    //    videoWidget->setMinimumSize(320, 240);
    //    player->setVideoOutput(videoWidget);

    //    //videoWidget->show();
    //    player->play();

//    QString str = "default";
//    DigitKeyboard kb(str);
//    kb.show();

    //显示主界面
    TMainPage mainPage;
    mainPage.show();

    return a.exec();
}
