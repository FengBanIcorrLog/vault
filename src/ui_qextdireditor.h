/********************************************************************************
** Form generated from reading UI file 'qextdireditor.ui'
**
** Created: Tue Dec 24 18:30:04 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QEXTDIREDITOR_H
#define UI_QEXTDIREDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QextDirEditor
{
public:
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QToolButton *toolButton;
    QToolButton *termButton;

    void setupUi(QWidget *QextDirEditor)
    {
        if (QextDirEditor->objectName().isEmpty())
            QextDirEditor->setObjectName(QString::fromUtf8("QextDirEditor"));
        QextDirEditor->resize(112, 30);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QextDirEditor->sizePolicy().hasHeightForWidth());
        QextDirEditor->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(QextDirEditor);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        comboBox = new QComboBox(QextDirEditor);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setEditable(true);

        horizontalLayout->addWidget(comboBox);

        toolButton = new QToolButton(QextDirEditor);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/go_jump_locationbar.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon);

        horizontalLayout->addWidget(toolButton);

        termButton = new QToolButton(QextDirEditor);
        termButton->setObjectName(QString::fromUtf8("termButton"));
        termButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/terminal.svg"), QSize(), QIcon::Normal, QIcon::Off);
        termButton->setIcon(icon1);

        horizontalLayout->addWidget(termButton);


        retranslateUi(QextDirEditor);

        QMetaObject::connectSlotsByName(QextDirEditor);
    } // setupUi

    void retranslateUi(QWidget *QextDirEditor)
    {
        Q_UNUSED(QextDirEditor);
    } // retranslateUi

};

namespace Ui {
    class QextDirEditor: public Ui_QextDirEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QEXTDIREDITOR_H
