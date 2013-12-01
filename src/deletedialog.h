#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>

namespace Ui {
    class DeleteDialog;
}

class FileDeleter;
class QFileInfo;

class DeleteDialog : public QDialog {
    Q_OBJECT
public:
    DeleteDialog(FileDeleter *d, QWidget *parent = 0);
    ~DeleteDialog();

protected:
    void changeEvent(QEvent *e);

private slots:
    void prepareProgress(int itemCount);
    void delProgress(int percent, const QString& item);
    void delError(const QString& itemOfFail);
    void endDelete(bool canceled);

private:
    Ui::DeleteDialog *ui;
};

#endif // DELETEDIALOG_H
