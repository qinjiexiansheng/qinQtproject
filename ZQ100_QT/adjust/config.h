/**********************************************************************
** Copyright (C) 2000 Trolltech AS.  All rights reserved.
**
** This file is part of Qt Designer.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/

#ifndef CONFIG_H
#define CONFIG_H

#include <QMap>
#include <QStringList>

class Config
{
public:
    typedef QMap< QString, QString > ConfigGroup;
    
    Config( const QString &fn );
    ~Config();
    
    void setGroup( const QString &gname );
    void writeEntry( const QString &key, const QString &value );
    void writeEntry( const QString &key, int num );
    
    QString readEntry( const QString &key, const QString &deflt = QString::null );
    int readNumEntry( const QString &key, int deflt = -1 );
    QStringList readListEntry( const QString &key, const QChar &sep );     

    void clearGroup();
    void write( const QString &fn = QString::null );
    
protected:
    void read();
    void parse( const QString &line );
    
    QMap< QString, ConfigGroup > groups;
    QMap< QString, ConfigGroup >::Iterator git;
    QString filename;

};

#endif
