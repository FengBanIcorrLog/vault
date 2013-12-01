#include "qextdireditor.h"
#include "ui_qextdireditor.h"

#include <QLineEdit>
#include <QCompleter>
#include <QDirModel>

QextDirEditor::QextDirEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QextDirEditor)
{
    ui->setupUi(this);
    connect(ui->comboBox->lineEdit(), SIGNAL(returnPressed()),
            ui->toolButton, SLOT(animateClick()));
    QCompleter *completer = new QCompleter(this);
    QDirModel *model = new QDirModel(this);
    completer->setModel(model);
    ui->comboBox->setModel(model);
    ui->comboBox->setCompleter(completer);
}

QextDirEditor::~QextDirEditor()
{
    delete ui;
}

QDir QextDirEditor::currentDir() const
{
    return QDir(ui->comboBox->currentText());
}

void QextDirEditor::setDir(const QDir &newDir)
{
    ui->comboBox->setEditText(newDir.canonicalPath());
}

void QextDirEditor::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void QextDirEditor::on_toolButton_clicked()
{
   emit dirChanged(currentDir());
}
