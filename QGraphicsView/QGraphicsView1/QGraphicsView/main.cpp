#include <QtCore/QCoreApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene scene;
    scene.addText("I love Qt programming.",QFont("Times",22,QFont::Bold));
    QGraphicsView view(&scene);
    view.show();
    return a.exec();
}
