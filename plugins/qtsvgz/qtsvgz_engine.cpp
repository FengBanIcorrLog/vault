/**************************************************************************
** Filename: qtsvgz_engine.cpp
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

#include "qtsvgz_engine.h"
#include "zlib/zlib.h"
#include <QIcon>
#include <QPainter>
#include <QPixmap>
#include <QSvgRenderer>
#include <QPixmapCache>
#include <QStyle>
#include <QApplication>
#include <QStyleOption>
#include <QFileInfo>
#include <QDataStream>
#include <QBuffer>
#include <QtDebug>

#define GZ_READ_BUFFER (256*1024)

#define GZ_OK 0
#define GZ_INVALID_OUTPUT_DEVICE -1
#define GZ_FILE_OPEN_ERROR -2
#define GZ_INVALID_STREAM -3
#define GZ_READ_ERROR -4
#define GZ_WRITE_ERROR -5

class QtSvgzImageIOHandlerPrivate : public QSharedData
{
public:
	explicit QtSvgzImageIOHandlerPrivate()
	{
		render = new QSvgRenderer;
	}

	~QtSvgzImageIOHandlerPrivate()
	{
		delete render;
		render = 0;
	}

	static int inflateFile(QIODevice *file, QIODevice* output)
	{
		if (!output)
			return GZ_INVALID_OUTPUT_DEVICE;

		quint64 compressedSize = file->size();

		uInt rep = compressedSize / GZ_READ_BUFFER;
		uInt rem = compressedSize % GZ_READ_BUFFER;
		uInt cur = 0;

		qint64 read;
		quint64 tot = 0;

		char buffer1[GZ_READ_BUFFER];
		char buffer2[GZ_READ_BUFFER];

		/* Allocate inflate state */
		z_stream zstr;
		zstr.zalloc = Z_NULL;
		zstr.zfree = Z_NULL;
		zstr.opaque = Z_NULL;
		zstr.next_in = Z_NULL;
		zstr.avail_in = 0;

		int zret;

		/*
			windowBits can also be greater than 15 for optional gzip decoding. Add
			32 to windowBits to enable zlib and gzip decoding with automatic header
			detection, or add 16 to decode only the gzip format (the zlib format will
			return a Z_DATA_ERROR.  If a gzip stream is being decoded, strm->adler is
			a crc32 instead of an adler32.
		*/
		if ( (zret = inflateInit2_(&zstr, MAX_WBITS + 16, ZLIB_VERSION, sizeof(z_stream))) != Z_OK ) {
			qDebug("Failed to initialize zlib");
			return GZ_INVALID_STREAM;
		}

		int szDecomp;

		// Decompress until deflate stream ends or end of file
		do {
			read = file->read(buffer1, cur < rep ? GZ_READ_BUFFER : rem);

			if (read == 0)
				break;
			if (read < 0) {
				(void)inflateEnd(&zstr);
				qDebug("Read error");
				return GZ_READ_ERROR;
			}

			cur++;
			tot += read;

			zstr.avail_in = (uInt) read;
			zstr.next_in = (Bytef*) buffer1;

			// Run inflate() on input until output buffer not full
			do {
				zstr.avail_out = GZ_READ_BUFFER;
				zstr.next_out = (Bytef*) buffer2;;

				zret = inflate(&zstr, Z_NO_FLUSH);

				switch (zret) {
					case Z_NEED_DICT:
					case Z_DATA_ERROR:
					case Z_MEM_ERROR:
						inflateEnd(&zstr);
						qDebug("zlib failed to decode file");
						return GZ_INVALID_STREAM;
					default:
						;
				}

				szDecomp = GZ_READ_BUFFER - zstr.avail_out;
				if (output->write(buffer2, szDecomp) != szDecomp) {
					inflateEnd(&zstr);
					qDebug("Write error");
					return GZ_WRITE_ERROR;
				}

			} while (zstr.avail_out == 0);

		} while (zret != Z_STREAM_END);

		inflateEnd(&zstr);

		return GZ_OK;
	}

	QSvgRenderer* render;
	QString svgFile;
};

QtSvgzImageIOHandler::QtSvgzImageIOHandler()
: d(new QtSvgzImageIOHandlerPrivate)
{
}

QtSvgzImageIOHandler::~QtSvgzImageIOHandler()
{
}

bool QtSvgzImageIOHandler::canRead() const
{
    return true;
}

#include <QtDebug>

bool QtSvgzImageIOHandler::read(QImage *image)
{
    QBuffer buffer;
    buffer.open(QBuffer::WriteOnly);
    if ( QtSvgzImageIOHandlerPrivate::inflateFile( device(), &buffer ) == GZ_OK) {
        d->render->load(buffer.data());
        *image = QImage(d->render->defaultSize(), QImage::Format_ARGB32_Premultiplied);
        if (image->size().isEmpty())
            return false;
        image->fill(0);
        QPainter painter(image);
        d->render->render(&painter);
        painter.end();
        return true;
    }
    return false;
}
