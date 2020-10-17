#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
#if 0
        QApplication a(argc, argv);
        QGraphicsScene scene;
        scene.addText("I love Qt programming.",QFont("Times",22,QFont::Bold));
        QGraphicsView view(&scene);
        view.show();
        return a.exec();
 #elif 1
        QApplication a(argc, argv);
        QPainterPath path; //����ͼ��
        path.moveTo(340,30);
        path.cubicTo(340,30,350,5,400,30);

        QGraphicsScene scene; //���峡��
        scene.addText("I love Qt programming.",QFont("Times",22,QFont::Bold));
        scene.addPath(path,QPen(Qt::blue),QBrush(Qt::red)); //���ͼ�ε������У������и��Ի�����

        QGraphicsView view(&scene);
        view.show();
        return a.exec();

 #endif

}
