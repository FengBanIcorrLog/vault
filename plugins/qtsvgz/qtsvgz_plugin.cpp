/**************************************************************************
** Filename: qtsvgz_plugin.cpp
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

#include "qtsvgz_plugin.h"
#include "qtsvgz_engine.h"

static const char GZ_ID1 = 0x1f;
static const char GZ_ID2 = 0x8b;

QtSvgzImageIOPlugin::QtSvgzImageIOPlugin(QObject* parent)
: QImageIOPlugin(parent)
{

}

QtSvgzImageIOPlugin::~QtSvgzImageIOPlugin()
{
}

QImageIOHandler* QtSvgzImageIOPlugin::create(QIODevice *device, const QByteArray &format) const
{
    Q_UNUSED(device);
    Q_UNUSED(format);
    return new QtSvgzImageIOHandler();
}

QImageIOPlugin::Capabilities QtSvgzImageIOPlugin::capabilities(QIODevice *device, const QByteArray &format) const
{
    Q_UNUSED(format);
    Capabilities detectedCap;
    if (!device)
        return detectedCap;
    QByteArray header = device->read(32);
    if (header.size()==32) {
        if (header.at(0) == GZ_ID1 &&
            header.at(1) == GZ_ID2 )
                detectedCap |= CanRead;
    }
    return detectedCap;
}

QStringList QtSvgzImageIOPlugin::keys() const
{
    return QStringList() << "svgz" << "SVGZ";
}

Q_EXPORT_PLUGIN2(svgz, QtSvgzImageIOPlugin)
