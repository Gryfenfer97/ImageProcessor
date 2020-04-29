#ifndef CONFIGDIALOG_HPP
#define CONFIGDIALOG_HPP


#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QDebug>
#include <QGridLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QFileDialog>
#include "ui_dialog.h"

#define CONFIG_FILE "../ImageProcessor/config.txt"



class ConfigDialog : public QDialog
{
    Q_OBJECT
private:

    Ui::Dialog ui;
    QMap<QString, QString> configMap;

    static void generateConfigFilename(QString filename, QMap<QString, QString> map);


private slots:
    void definePath();
    void closeSlot();

public:
    ConfigDialog();
    ConfigDialog(QString configFilename);

    static QMap<QString, QString> loadConfig();
    QMap<QString, QString> getConfigMap();

};

#endif // CONFIGDIALOG_HPP
