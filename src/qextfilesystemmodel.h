#ifndef QEXTFILESYSTEMMODEL_H
#define QEXTFILESYSTEMMODEL_H

#include <QFileSystemModel>

class QextFileSystemModel : public QFileSystemModel
{
Q_OBJECT
public:
    explicit QextFileSystemModel(QObject *parent = 0);

signals:

public slots:

};

#endif // QEXTFILESYSTEMMODEL_H
