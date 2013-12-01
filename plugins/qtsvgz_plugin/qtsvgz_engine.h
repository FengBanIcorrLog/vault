/**************************************************************************
** Filename: qtsvgz_engine.h
**
** Copyright (C) 2010 Martin Ribelotta. Based on QtSvgzIconEngine.
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

#ifndef QTSVGZ_ENGINE_H
#define QTSVGZ_ENGINE_H

#include <QImageIOHandler>
#include <QSharedData>

class QtSvgzImageIOHandlerPrivate;

class QtSvgzImageIOHandler : public QImageIOHandler
{
public:
        QtSvgzImageIOHandler();
        virtual ~QtSvgzImageIOHandler();

        virtual bool canRead() const;
        virtual bool read(QImage *image);

private:
        QSharedDataPointer<QtSvgzImageIOHandlerPrivate> d;

};

#endif // QTSVGZ_ENGINE_H
