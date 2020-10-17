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

#include "config.h"

#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>

Config::Config( const QString &fn ) : filename( fn ){
    git = groups.end();
    read();
}

Config::~Config(){
    write();
}

void Config::setGroup( const QString &gname ){
    QMap< QString, ConfigGroup>::Iterator it = groups.find( gname );
    if ( it == groups.end() ) {
        ConfigGroup *grp = new ConfigGroup;
        git = groups.insert( gname, *grp );
        return;
    }
    git = it;
}

void Config::writeEntry( const QString &key, const QString &value ){
    if ( git == groups.end() ) {
        qDebug()<<"no group set " ;
        return;
    }
    ( *git ).insert( key, value );
}

void Config::writeEntry( const QString &key, int num ){
    QString s;
    s.setNum( num );
    writeEntry( key, s );
}


QString Config::readEntry( const QString &key, const QString &deflt ){
    if ( git == groups.end() ) {
        qDebug()<<"no group set" ;
        return deflt;
    }
    ConfigGroup::Iterator it = ( *git ).find( key );
    if ( it != ( *git ).end() )
        return *it;
    else
        return deflt;
}

int Config::readNumEntry( const QString &key, int deflt ){
    QString s = readEntry( key );
    if ( s.isEmpty() )
        return deflt;
    else
        return s.toInt();
}

void Config::clearGroup(){
    if ( git == groups.end() ) {
        qDebug()<< "no group set" ;
        return;
    }
    ( *git ).clear();
}

void Config::write( const QString &fn ){
    if ( !fn.isEmpty() )
        filename = fn;

    QFile f( filename );
    if ( !f.open( QIODevice::WriteOnly) ) {
        qDebug()<<"could not open for writing: "<<qPrintable(filename);
        git = groups.end();
        return;
    }

    QTextStream s( &f );
    QMap< QString, ConfigGroup >::Iterator g_it = groups.begin();
    for ( ; g_it != groups.end(); ++g_it ) {
        s << "[" << g_it.key() << "]" << "\n";
        ConfigGroup::Iterator e_it = ( *g_it ).begin();
        for ( ; e_it != ( *g_it ).end(); ++e_it )
            s << e_it.key() << " = " << *e_it << "\n";
    }
    f.close();
}

void Config::read()
{
    if ( !QFileInfo( filename ).exists() ) {
        qDebug()<<qPrintable(filename)<<"  doesn't exist";
        git = groups.end();
        return;
    }

    QFile f( filename );
    if ( !f.open( QIODevice::ReadOnly) ) {
        qDebug()<<"could not open for reading: "<<qPrintable(filename);
        git = groups.end();
        return;
    }
    QTextStream s( &f );
    QString line;
    while ( !s.atEnd() ) {
        line = s.readLine();
        parse( line );
    }
    f.close();
}

void Config::parse( const QString &l )
{
    QString line = l.simplified();
    if ( line[ 0 ] == QChar( '[' ) ) {
        QString gname = line;
        gname = gname.remove( 0, 1 );
	if ( gname[ (int)gname.length() - 1 ] == QChar( ']' ) )
	    gname = gname.remove( gname.length() - 1, 1 );
	ConfigGroup *grp = new ConfigGroup;
	git = groups.insert( gname, *grp );
    } else {
	if ( git == groups.end() ) {
        qDebug()<<"line `%s' out of group"<<qPrintable(line);
	    return;
	}
    QStringList lst = line.split('=');
    if ( lst.count() != 2 && line.contains('=') == -1 ) {
        qDebug()<<"corrupted line: "<<qPrintable(line)<<"in group:  "<<qPrintable(git.key());
	    return;
	}
    ( *git ).insert( lst[ 0 ].simplified(), lst[ 1 ].simplified() );
    }
}
