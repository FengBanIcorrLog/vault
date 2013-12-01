#include "deletedialog.h"
#include "ui_deletedialog.h"

#include "filedeleter.h"

#include <QFileInfo>

DeleteDialog::DeleteDialog(FileDeleter *d, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteDialog)
{
    ui->setupUi(this);
    connect(d, SIGNAL(prepareProgress(int)), this, SLOT(prepareProgress(int)));
    connect(d, SIGNAL(delProgress(int,QString)),
            this, SLOT(delProgress(int,QString)));
    connect(d, SIGNAL(endDelete(bool)), this, SLOT(endDelete(bool)));
    connect(d, SIGNAL(fail(QString)),
            this, SLOT(delError(QString)));
    connect(ui->buttonAbort, SIGNAL(clicked()), d, SLOT(abortDelete()));
    connect(ui->buttonClose, SIGNAL(clicked()), this, SLOT(close()));
}

DeleteDialog::~DeleteDialog()
{
    delete ui;
}

void DeleteDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DeleteDialog::prepareProgress(int itemCount)
{
    ui->buttonAbort->setEnabled(true);
    ui->buttonClose->setEnabled(false);
    ui->progressBar->setValue(0);
    ui->label->setText(tr("Preparing to delete %1 files").arg(itemCount));
}

void DeleteDialog::delProgress(int percent, const QString &item)
{
    ui->progressBar->setValue(percent);
    ui->label->setText(tr("Deleting %1").arg(item));
}

void DeleteDialog::delError(const QString &itemOfFail)
{
    ui->label->setText(tr("Error deleting %1").arg(itemOfFail));
}

void DeleteDialog::endDelete(bool canceled)
{
    if (!canceled)
        ui->label->setText(tr("Delete Finished Ok"));
    ui->buttonAbort->setEnabled(false);
    ui->buttonClose->setEnabled(true);
}
