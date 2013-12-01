#include "qextfilesystemcontroller.h"
#include "qextfilesystemmodel.h"

#include <QStack>

class QextFileSystemControllerPrivate : public QObject {
public:
    QAbstractItemView *view;
    QextFileSystemModel *fsModel;
    QextFileSystemController *parent;
    QStack<QDir> prevStack;
    QStack<QDir> nextStack;
    QDir currentLocation;
    QModelIndex currentModelIndex;

    QextFileSystemControllerPrivate(QextFileSystemController *p)
    {
        parent = p;
        fsModel = 0l;
        view = 0l;
    }

    void doChDir(const QDir& dir)
    {
        QString path = dir.canonicalPath();
        if (fsModel)
            currentModelIndex = fsModel->setRootPath(path);
        if (view)
            view->setRootIndex(fsModel->index(path));

    }

    bool canGoNext()
    {
        return !nextStack.isEmpty();
    }

    bool canGoPrev()
    {
        return !prevStack.isEmpty();
    }

    bool canGoUp()
    {
        return !fsModel->rootDirectory().isRoot();
    }


};

QextFileSystemController::QextFileSystemController(QAbstractItemView *view, QObject *parent) :
    QObject(parent),
    self(new QextFileSystemControllerPrivate(this))
{
    Q_D(QextFileSystemController);
    d->view = view;
    d->fsModel = new QextFileSystemModel(this);
    //d->currentLocation = QDir::rootPath();
    d->currentLocation = QDir::currentPath();
    d->view->setModel(d->fsModel);
    refresh();
}

QextFileSystemController::~QextFileSystemController()
{
    delete self;
}

QString QextFileSystemController::path(const QModelIndex &index) const
{
    const Q_D(QextFileSystemController);
    return d->fsModel->filePath(index);
}

QString QextFileSystemController::path() const
{
    const Q_D(QextFileSystemController);
    return d->currentLocation.absolutePath();
}

QFileInfoList QextFileSystemController::selectedInfoItems() const
{
    const Q_D(QextFileSystemController);
    QFileInfoList selInfo;
    foreach(QModelIndex index, d->view->selectionModel()->selectedRows())
        selInfo.append(QFileInfo(path(index)));
    return selInfo;
}

bool QextFileSystemController::onProgress()
{
    Q_D(QextFileSystemController);
    return d->fsModel->rowCount(d->currentModelIndex) == 0;
}

void QextFileSystemController::refresh()
{
    Q_D(QextFileSystemController);
    QDir oldPath = d->fsModel->rootDirectory();
    d->doChDir(d->currentLocation);
    if (oldPath!=d->currentLocation)
        emit dirChanged(d->currentLocation);
    emit canBackward(d->canGoPrev());
    emit canFordward(d->canGoNext());
    emit canUp(d->canGoUp());
}

void QextFileSystemController::clearNextHistory()
{
    Q_D(QextFileSystemController);
    d->nextStack.clear();
    refresh();
}

void QextFileSystemController::clearPrevHistory()
{
    Q_D(QextFileSystemController);
    d->prevStack.clear();
    refresh();
}

void QextFileSystemController::goDir(const QDir &dir)
{
    Q_D(QextFileSystemController);
    clearNextHistory();
    d->prevStack.push(d->fsModel->rootPath());
    d->currentLocation = dir;
    refresh();
}

void QextFileSystemController::goHome()
{
    goDir(QDir::home());
}

void QextFileSystemController::goUp()
{
    Q_D(QextFileSystemController);
    if ( d->canGoUp() )
    {
        goDir( QDir( d->fsModel->rootPath() + QDir::separator() + ".." ) );
    } // end if cangoup
}

void QextFileSystemController::goBackward()
{
    Q_D(QextFileSystemController);
    if (d->canGoPrev()) {
        d->nextStack.push(d->fsModel->rootDirectory());
        d->currentLocation =  d->prevStack.pop();
    }
    refresh();
}

void QextFileSystemController::goFordward()
{
    Q_D(QextFileSystemController);
    if (d->canGoNext()) {
        d->prevStack.push(d->fsModel->rootDirectory());
        d->currentLocation = d->nextStack.pop();
   }
   refresh();
}
