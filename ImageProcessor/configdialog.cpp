#include "configdialog.hpp"



ConfigDialog::ConfigDialog() : QDialog()
{
    this->setWindowTitle(tr("Configuration"));
    this->setFixedSize(300,200);

    ui.setupUi(this);

    ui.modeComboBox->addItem("Wrap");
    ui.modeComboBox->addItem("Crop");

    configMap = loadConfig();
    ui.modeComboBox->setCurrentText(configMap["Mode"]);
    ui.configPathLineEdit->setText(configMap["MatrixPath"]);

    connect(ui.configPathBtn, SIGNAL(clicked()), this, SLOT(definePath()));
    connect(ui.buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(closeSlot()));

}

QMap<QString, QString> ConfigDialog::loadConfig(){
    QFile file(CONFIG_FILE);
    QMap<QString, QString> configMap;
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        QString line;
        QStringList lineSplited;
        while(!stream.atEnd()){
            stream >> line;
            lineSplited = line.split("=");
            configMap[lineSplited[0]] = lineSplited[1];
        }

    }
    else{
        configMap["Mode"] = "Wrap";
        configMap["MatrixPath"] = "ConvolutionMatrix.txt";
        generateConfigFilename(CONFIG_FILE, configMap);
    }
    return configMap;
}

void ConfigDialog::generateConfigFilename(QString filename, QMap<QString, QString> configMap){
    QFile file(filename);
    QMapIterator<QString, QString> map(configMap);
    if(file.open(QIODevice::Append)){
        QTextStream stream(&file);
        while(map.hasNext()){
            map.next();
            stream << map.key() << "=" << map.value();
            if(map.hasNext()){
                stream << "\n";
            }
        }
    }
}

void ConfigDialog::definePath(){
    QFileDialog dialog(this, tr("Open Matrix File"), ".", "(*.txt)");
    QString filename;
    if(dialog.exec()){
        filename = dialog.selectedFiles().first();
        ui.configPathLineEdit->setText(filename);
    }

}

void ConfigDialog::closeSlot(){
    QFile file(CONFIG_FILE);
    configMap["Mode"] = ui.modeComboBox->currentText();
    configMap["MatrixPath"] = ui.configPathLineEdit->text();
    QMapIterator<QString, QString> map(configMap);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        while(map.hasNext()){
            map.next();
            stream << map.key() << "=" << map.value();
            if(map.hasNext()){
                stream << endl;
            }
        }

    }
}


QMap<QString, QString> ConfigDialog::getConfigMap(){
    return configMap;
}
