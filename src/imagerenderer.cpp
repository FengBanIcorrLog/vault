#include "imagerenderer.h"

ImageRenderer::ImageRenderer(const QSize &size, const QString &path, QObject *parent, const char *member) :
    QObject(parent)
{
    this->size = size;
    this->path = path;
    connect(this, SIGNAL(finish(QImage*)),
            parent, member,
            Qt::QueuedConnection);
}

static inline bool needScale(const QSize& container, const QSize& contained)
{
    return (contained.width()>container.width() ||
            container.height()>container.height());
}

void ImageRenderer::run()
{
    QImage image(path);
    if (!path.isEmpty()) {
        if (!needScale(size, image.size()))
            emit finish(new QImage(image));
        else
            emit finish(new QImage(image.scaled(size, Qt::KeepAspectRatio,
                                            Qt::SmoothTransformation)));
    }
}
