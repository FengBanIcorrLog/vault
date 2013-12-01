#ifndef IMAGERENDERER_H
#define IMAGERENDERER_H

#include <QObject>
#include <QRunnable>
#include <QImage>

/**
  Read and scale (if necesary) image to specific container size
 */
class ImageRenderer : public QObject, public QRunnable
{
Q_OBJECT
public:
    /**
      Construct image renderer for image into "path" with maximum size of "size"<br>
      Notify to "parent"->"member"<br>
      Member must be receive a QImage* parameter

      @param size Size of the container
      @param path Path of image to preview
      @param parent Objeto to notify the result
      @param member SLOT with QImage* param to receive result
     */
    explicit ImageRenderer(const QSize& size, const QString& path, QObject *parent, const char *member);

    /**
      Process image read and scaling (if necesary) in a thread pool
     */
    virtual void run();

signals:
    /**
      Emited when process finished<br>
      You need destroy a image parameter manualy with "delete image"

      @param image Pointer to dynamic image
     */
    void finish(QImage* image);

private:
    QString path;
    QSize size;
};

#endif // IMAGERENDERER_H
