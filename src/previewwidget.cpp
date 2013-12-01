#include "previewwidget.h"
#include "ui_previewwidget.h"

#include <QImage>
#include <QImageReader>
#include <QMovie>
#include <QThreadPool>
#include <QFileIconProvider>

#include <QtDebug>

#include "imagerenderer.h"

#define KBYTES 1024.0
#define MBYTES (KBYTES*1024.0)
#define GBYTES (MBYTES*1024.0)
#define TBYTES (GBYTES*1024.0)

PreviewWidget::PreviewWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PreviewWidget)
{
	iconProvider = new QFileIconProvider;
	pool = new QThreadPool(this);
	pool->setExpiryTimeout(5000);
	pool->setMaxThreadCount(2);
	ui->setupUi(this);
}

PreviewWidget::~PreviewWidget()
{
	delete iconProvider;
	delete ui;
}

void PreviewWidget::startPreview(const QFileInfo &info)
{
	/*if( info.isDir() )
		ui->label->setPixmap(QPixmap(":/folder.svg"));
	else*/ if( QImageReader(info.absoluteFilePath()).canRead() )
	{
		QByteArray imageFormat = QImageReader::imageFormat(info.absoluteFilePath());
		if( imageFormat == "gif" || imageFormat == "mng" ) // Supports animation // TODO file size limit for animation
		{
			QMovie* movie = new QMovie(info.absoluteFilePath());
			//QImageReader *imgReader = QImageReader(info.absoluteFilePath());

			// Make sure the GIF was loaded correctly
			if( movie->isValid() )
			{
				QSize imgSize = QImageReader(info.absoluteFilePath()).size();
#if 1
				movie->setScaledSize(ui->label->size());
#else
				// Scale the movie to fit into the widget box
				if( imgSize.width() > ui->label->size().width() && imgSize.height() > ui->label->size().height() )
					if( ui->label->size().width() / imgSize.width() < ui->label->size().height() / imgSize.height() )
						movie->setScaledSize(QSize( // Scale relatively to the image width
							ui->label->size().width(),
							imgSize.height() * (ui->label->size().width() / imgSize.width())
						));
					else
						movie->setScaledSize(QSize( // Scale relatively to the image height
							ui->label->size().width() * (ui->label->size().height() / imgSize.height()),
							ui->label->size().height()
						));
				else if( imgSize.width() > ui->label->size().width() )
					movie->setScaledSize(QSize( // Scale relatively to the image width
						ui->label->size().width(),
						imgSize.height() * (ui->label->size().width() / imgSize.width())
					));
				else if( imgSize.height() > ui->label->size().height() )
					movie->setScaledSize(QSize( // Scale relatively to the image height
						imgSize.width() * (ui->label->size().height() / imgSize.height()),
						ui->label->size().height()
					));
				// end Scaling
#endif
				// Play GIF
				ui->label->setMovie(movie);
				movie->start();
			}
		}
		else // Static picture
			pool->start(new ImageRenderer(ui->label->size(),
										  info.absoluteFilePath(),
										  this, SLOT(finished(QImage*))));
	}
	else
		ui->label->setPixmap(iconProvider->icon(info).pixmap(128));
	showFileInfo(info);
}

static inline QString humanReadableSize(int cuantity)
{
	QString prefix;
	double factor = 1.0;
	if (cuantity < KBYTES) {
		prefix = QObject::tr(" Bytes");
		factor = 1.0;
	} else if (cuantity < MBYTES) {
		prefix = QObject::tr(" KB");
		factor = KBYTES;
	} else if (cuantity < GBYTES) {
		prefix = QObject::tr(" MB");
		factor = MBYTES;
	} else if (cuantity < TBYTES) {
		prefix = QObject::tr(" GB");
		factor = GBYTES;
	} else {
		prefix = QObject::tr(" TB");
		factor = TBYTES;
	}
	return QString("%1 %2").arg(cuantity/factor, 0, 'f', 2, QChar('0')).arg(prefix);
}

static inline QString humanReadableType(const QFileInfo& info)
{
	if (info.isDir())
		return QObject::tr("Directory");
	if (info.isBundle())
		return QObject::tr("Mac Bundled");
	if (info.isExecutable())
		return QObject::tr("Executable");
	return info.completeSuffix();
}

void PreviewWidget::showFileInfo(const QFileInfo &info)
{
	ui->textBrowser->setHtml(QString(
			"<html>"
			"<body>"
			"<div><h2>%1</h2></div>"
			"<div><b>File type: </b>%2</div>"
			"<div><b>Size: </b>%3</div>"
			"</body>"
			"</html>"
	)
	 .arg(info.fileName())
	 .arg(humanReadableType(info))
	 .arg(humanReadableSize(info.size())));
}

void PreviewWidget::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
		default:
			break;
	}
}

void PreviewWidget::finished(QImage *tmpImage)
{
	ui->label->setPixmap(QPixmap::fromImage(*tmpImage));
	delete tmpImage;
}
