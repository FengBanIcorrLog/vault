#ifndef QEXTDIREDITOR_H
#define QEXTDIREDITOR_H

#include <QWidget>
#include <QDir>

namespace Ui {
    class QextDirEditor;
}


/**
  Editor of URLs with directory autocompletion
 */
class QextDirEditor : public QWidget {
    Q_OBJECT
public:
    QextDirEditor(QWidget *parent = 0);
    ~QextDirEditor();

    /**
      @return Current directory of editor
     */
    QDir currentDir() const;

signals:
    /**
      Emited when enter is pressed on URL editor,
      item of combo box is changed, or "Go" button is pressed
      @param newDir The new directory edited
     */
    void dirChanged(const QDir& newDir);

public slots:
    /**
      Change current directory of editor<br>
      The displayed text is the result of newDir.canonicalFilePath() method

      @param newDir The new directory to show
     */
    void setDir(const QDir& newDir);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::QextDirEditor *ui;

private slots:
    void on_toolButton_clicked();
};

#endif // QEXTDIREDITOR_H
