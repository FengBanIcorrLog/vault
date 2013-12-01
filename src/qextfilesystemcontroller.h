#ifndef QEXTFILESYSTEMCONTROLLER_H
#define QEXTFILESYSTEMCONTROLLER_H

#include <QObject>
#include <QAbstractItemView>
#include <QFileInfo>

class QextFileSystemControllerPrivate;
class QDir;

/**
  Object controller to provide connection between the filesystem model and viewer<br>
  The model is created by the controller and it is a @ref QextFileSystemModel type

  @see QextFileSystemModel
 */
class QextFileSystemController : public QObject
{
Q_OBJECT
public:
    /**
      Construct a controller for "view" viewer
      @param view Viewer such as QTreeView or QTableView
      @param parent Owner of object
     */
    explicit QextFileSystemController(QAbstractItemView *view, QObject *parent = 0);
    virtual ~QextFileSystemController();

    /**
      @return Path of index, or empty string if index is not into current model
     */
    QString path(const QModelIndex& index) const;

    /**
      @return Path of current index
      @see QextFileSystemController::path(const QModelIndex& index) const;
     */
    QString path() const;

    /**
      @return List of selected file info objects
     */
    QFileInfoList selectedInfoItems() const;

    /**
      @return True if model is processing directory, false if model is ready
     */
    bool onProgress();

signals:
    /**
      Emitted with up direction capavility is changed
      @param en True if can go up
     */
    void canUp(bool en);
    /**
      Emitted with back direction capavility is changed
      @param en True if can go back
     */
    void canBackward(bool en);
    /**
      Emitted with fordward direction capavility is changed
      @param en True if can go fordward
     */
    void canFordward(bool en);
    /**
      Emitted with directory change
      @param dir New current directory
     */
    void dirChanged(const QDir& dir);

public slots:
    /**
      Force reload of currentdirectory
     */
    void refresh();
    /**
      Clear next history list
     */
    void clearNextHistory();
    /**
      Clear previus history list
     */
    void clearPrevHistory();
    /**
      Change directory

      @param path The new directory
     */
    void goDir(const QDir& path);
    /**
      Change directory to home (defined by QDir::home())
     */
    void goHome();
    /**
      Up one level (if posible) into directory hierarchy
     */
    void goUp();
    /**
      Move to inmediate previous directory in history
     */
    void goBackward();
    /**
      Move to inmediate next directory in history
     */
    void goFordward();

private:
    QextFileSystemControllerPrivate *self;
    Q_DECLARE_PRIVATE_D(self, QextFileSystemController);
};

#endif // QEXTFILESYSTEMCONTROLLER_H
