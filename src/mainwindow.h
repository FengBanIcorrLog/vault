#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class QextFileSystemController;
class QModelIndex;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QextFileSystemController *controller;
    QIcon iconCopy;
    QIcon iconCut;
    QIcon iconPaste;
    QIcon iconDel;

    enum CopyCutAction_t {
        ActionNone,
        ActionCopy,
        ActionCut
    };

    CopyCutAction_t lastCopyCut;

    QMenu *makeBasicMenu();
    bool isPasteEnabled();

    void doCopyCut(CopyCutAction_t action);

private slots:
    void on_tableView_customContextMenuRequested(QPoint pos);
    void currentRowChanged(const QModelIndex& curr, const QModelIndex& prev);
    void adjustView();
    void on_tableView_activated(const QModelIndex& index);
    void on_actionAtUp_triggered();
    void on_actionFordward_triggered();
    void on_actionBackward_triggered();
    void on_actionAtHome_triggered();
    void on_action_Exit_triggered();
    void copySelection();
    void cutSelection();
    void pasteSelection();
    void delSelection();
};

#endif // MAINWINDOW_H
