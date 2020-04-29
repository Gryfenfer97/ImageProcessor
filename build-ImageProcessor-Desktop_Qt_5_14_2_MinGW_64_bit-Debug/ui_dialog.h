/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QComboBox *modeComboBox;
    QLineEdit *configPathLineEdit;
    QPushButton *configPathBtn;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(300, 200);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 160, 271, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 50, 47, 13));
        modeComboBox = new QComboBox(Dialog);
        modeComboBox->setObjectName(QString::fromUtf8("modeComboBox"));
        modeComboBox->setGeometry(QRect(130, 50, 111, 22));
        configPathLineEdit = new QLineEdit(Dialog);
        configPathLineEdit->setObjectName(QString::fromUtf8("configPathLineEdit"));
        configPathLineEdit->setGeometry(QRect(80, 100, 121, 20));
        configPathLineEdit->setReadOnly(true);
        configPathBtn = new QPushButton(Dialog);
        configPathBtn->setObjectName(QString::fromUtf8("configPathBtn"));
        configPathBtn->setGeometry(QRect(210, 100, 31, 21));

        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "Mode :", nullptr));
        configPathLineEdit->setPlaceholderText(QCoreApplication::translate("Dialog", "Convolution Matrix path", nullptr));
        configPathBtn->setText(QCoreApplication::translate("Dialog", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
