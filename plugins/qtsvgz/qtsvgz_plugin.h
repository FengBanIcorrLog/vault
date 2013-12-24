/**************************************************************************
** Filename: qtsvgz_plugin.h
**
** Copyright (C) 2007 Angius Fabrizio. All rights reserved.
**
** This file is part of the OSDaB project (http://osdab.sourceforge.net/).
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See the file LICENSE.GPL that came with this software distribution or
** visit http://www.gnu.org/copyleft/gpl.html for GPL licensing information.
**
**************************************************************************/

#ifndef QTSVGZ_PLUGIN_H
#define QTSVGZ_PLUGIN_H

#include <QImageIOPlugin>

class QtSvgzImageIOPlugin : public QImageIOPlugin
{
	Q_OBJECT

public:
        QtSvgzImageIOPlugin(QObject* parent = 0);
        virtual ~QtSvgzImageIOPlugin();

        virtual QImageIOHandler* create(QIODevice *device, const QByteArray &format) const;
        virtual Capabilities capabilities(QIODevice *device, const QByteArray &format) const;
	virtual QStringList keys() const;
};

#endif // QTSVGZ_PLUGIN_H
