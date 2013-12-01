#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qextfilesystemcontroller.h"
#include "qextdireditor.h"
#include "qtcopydialog.h"
#include "filedeleter.h"
#include "deletedialog.h"

#include <QDir>
#include <QFileInfo>
#include <QTimer>
#include <QClipboard>
#include <QMimeData>
#include <QMessageBox>
#include <QPixmap>
#include <QUrl>
#include <QtGui>

#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowIcon(QIcon(":/icons/icon.svg"));

    iconCopy = QIcon(":/icons/edit_copy.svg");
    iconCut = QIcon(":/icons/edit_cut.svg");
    iconPaste = QIcon(":/icons/edit_paste.svg");
    iconDel = QIcon(":/icons/edit_delete.svg");

    ui->setupUi(this);
    QextDirEditor *addressBar = new QextDirEditor(this);
    ui->mainToolBar->addWidget(addressBar);

    controller = new QextFileSystemController(ui->tableView, this);
    connect(controller, SIGNAL(canBackward(bool)),
            ui->actionBackward, SLOT(setEnabled(bool)));
    connect(controller, SIGNAL(canFordward(bool)),
            ui->actionFordward, SLOT(setEnabled(bool)));
    connect(controller, SIGNAL(canUp(bool)),
            ui->actionAtUp, SLOT(setEnabled(bool)));
    connect(addressBar, SIGNAL(dirChanged(QDir)),
            controller, SLOT(goDir(QDir)));
    connect(controller, SIGNAL(dirChanged(QDir)),
            addressBar, SLOT(setDir(QDir)));
    connect(controller, SIGNAL(dirChanged(QDir)),
            this, SLOT(adjustView()));
    connect(ui->tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(currentRowChanged(QModelIndex,QModelIndex)));

    controller->refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QMenu *MainWindow::makeBasicMenu()
{
    bool haveSelection = !controller->selectedInfoItems().isEmpty();
    QMenu *menu = new QMenu(this);
    QAction *copy = menu->addAction(iconCopy, tr("Cut"), this, SLOT(cutSelection()));
    QAction *cut = menu->addAction(iconCut, tr("Copy"), this, SLOT(copySelection()));
    QAction *paste = menu->addAction(iconPaste, tr("Paste"), this, SLOT(pasteSelection()));
    menu->addSeparator();
    QAction *del = menu->addAction(iconDel, tr("Delete"), this, SLOT(delSelection()));
    copy->setEnabled(haveSelection);
    cut->setEnabled(haveSelection);
    paste->setEnabled(isPasteEnabled());
    del->setEnabled(haveSelection);
    // TODO
    return menu;
}

bool MainWindow::isPasteEnabled()
{
    const QMimeData *mime = QApplication::clipboard()->mimeData();
    return mime && mime->hasUrls();
}

void MainWindow::doCopyCut(CopyCutAction_t action)
{
    QList<QUrl> urlList;
    foreach(QFileInfo info, controller->selectedInfoItems())
        urlList.append(QUrl::fromLocalFile(info.canonicalFilePath()));
    QMimeData *mime = new QMimeData();
    mime->setUrls(urlList);
    QApplication::clipboard()->setMimeData(mime);
    lastCopyCut = action;
}

void MainWindow::copySelection()
{
    doCopyCut(ActionCopy);
}

void MainWindow::cutSelection()
{
    doCopyCut(ActionCut);
}

void MainWindow::pasteSelection()
{
    const QMimeData *mime = QApplication::clipboard()->mimeData();
    if (mime && mime->hasUrls()) {
        QString destinationPath = controller->path();
        QStringList fileList;
        foreach(QUrl url, mime->urls())
            fileList.append(url.toLocalFile());
        QtFileCopier fileCopier;
        QtCopyDialog d(&fileCopier, this);
        switch(lastCopyCut) {
        case ActionCopy:
            fileCopier.copyFiles(fileList, destinationPath);
            break;
        case ActionCut:
            fileCopier.moveFiles(fileList, destinationPath);
            break;
        default:
            break;
        }
        d.exec();
    }
}

void MainWindow::delSelection()
{
    FileDeleter deleter(controller->selectedInfoItems(), this);
    DeleteDialog dialog(&deleter, this);
    deleter.start();
    dialog.exec();
}

void MainWindow::on_action_Exit_triggered()
{
    close();
}

void MainWindow::on_actionAtHome_triggered()
{
    controller->goHome();
}

void MainWindow::on_actionBackward_triggered()
{
    controller->goBackward();
}

void MainWindow::on_actionFordward_triggered()
{
    controller->goFordward();
}

void MainWindow::on_actionAtUp_triggered()
{
    controller->goUp();
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QFileInfo pathInfo(controller->path(index));
    if (pathInfo.isDir())
        controller->goDir(QDir(pathInfo.absoluteFilePath()));
}

void MainWindow::adjustView()
{
    if (controller->onProgress())
        QTimer::singleShot(0, this, SLOT(adjustView()));
    else
        QTimer::singleShot(0, ui->tableView, SLOT(resizeColumnsToContents()));

    setWindowTitle(controller->path());
}

void MainWindow::currentRowChanged(const QModelIndex &curr, const QModelIndex &prev)
{
    Q_UNUSED(prev);
    ui->previewWidget->startPreview(QFileInfo(controller->path(curr)));
}

void MainWindow::on_tableView_customContextMenuRequested(QPoint pos)
{
    Q_UNUSED(pos);
    QMenu *menu = makeBasicMenu();
    connect(menu, SIGNAL(aboutToHide()), menu, SLOT(deleteLater()));
    menu->exec(QCursor::pos());
}
