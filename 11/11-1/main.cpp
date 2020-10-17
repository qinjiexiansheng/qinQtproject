
#include <QDebug>

void Sample_1()
{
    QString s = "add";

    s.append(" ");    // "add "
    s.append("Qt");   // "add Qt"
    s.prepend(" ");   // " add Qt"
    s.prepend("C++"); // "C++ add Qt"

    qDebug() << s;

    s.replace("add", "&"); // "C++ & Qt"

    qDebug() << s;
}

void Sample_2()
{
    QString s = "";
    int index = 0;

    s.sprintf("%d. I'm %s, thank you!", 1, "Delphi Tang"); // "1. I'm Delphi Tang, thank you!"

    qDebug() << s;

    index = s.indexOf(",");

    s = s.mid(0, index);   // "1. I'm Delphi Tang"

    qDebug() << s;

    index = s.indexOf(".");

    s = s.mid(index + 1, s.length()); // " I'm Delphi Tang"
    s = s.trimmed();                  // "I'm Delphi Tang"

    qDebug() << s;

    index = s.indexOf(" ");

    s = s.mid(index + 1, s.length()); // "Delphi Tang"

    qDebug() << s;
}

void Sample_3(QString* a, int len)
{
    for(int i=0; i<len; i++)
    {
        for(int j=i+1; j<len; j++)
        {
            if( a[j] < a[i] )
            {
                QString tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

int main()
{
    qDebug() << "Sample_1:";

    Sample_1();

    qDebug() << endl;
    qDebug() << "Sample_2:";

    Sample_2();

    qDebug() << endl;
    qDebug() << "Sample_3:";

    QString company[5] =
    {
        QString("Oracle"),
        QString("Borland"),
        QString("Microsoft"),
        QString("IBM"),
        QString("D.T.Software")
    };

    Sample_3(company, 5);

    for(int i=0; i<5; i++)
    {
        qDebug() << company[i];
    }

    return 0;
}
