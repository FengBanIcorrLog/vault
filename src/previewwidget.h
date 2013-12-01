#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QWidget>
#include <QFileInfo>

namespace Ui {
    class PreviewWidget;
}

class QThreadPool;
class QFileIconProvider;

/**
  <p>Widget to preview file</p>
  <p>Only preview images and folder information</p>
 */
class PreviewWidget : public QWidget {
    Q_OBJECT
public:
    PreviewWidget(QWidget *parent = 0);
    ~PreviewWidget();

public slots:
    /**
      Init previsualization of file defined by "info"
      @param info File to previsualized
     */
    void startPreview(const QFileInfo& info);

    /**
      Show formated file information as text
      @param info File to preview
     */
    void showFileInfo(const QFileInfo& info);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::PreviewWidget *ui;
    QThreadPool *pool;
    QFileIconProvider *iconProvider;

private slots:
    void finished(QImage *tmpImage);
};

#endif // PREVIEWWIDGET_H
