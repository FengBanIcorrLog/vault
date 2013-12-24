/********************************************************************************
** Form generated from reading UI file 'previewwidget.ui'
**
** Created: Tue Dec 24 18:30:04 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREVIEWWIDGET_H
#define UI_PREVIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreviewWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *PreviewWidget)
    {
        if (PreviewWidget->objectName().isEmpty())
            PreviewWidget->setObjectName(QString::fromUtf8("PreviewWidget"));
        PreviewWidget->resize(274, 231);
        verticalLayout = new QVBoxLayout(PreviewWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(PreviewWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(128, 128));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        textBrowser = new QTextBrowser(PreviewWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(textBrowser);


        retranslateUi(PreviewWidget);

        QMetaObject::connectSlotsByName(PreviewWidget);
    } // setupUi

    void retranslateUi(QWidget *PreviewWidget)
    {
        PreviewWidget->setWindowTitle(QApplication::translate("PreviewWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PreviewWidget: public Ui_PreviewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREVIEWWIDGET_H
