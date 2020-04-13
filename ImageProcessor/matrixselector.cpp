#include "matrixselector.hpp"

MatrixSelector::MatrixSelector(QWidget *parent) : QWidget(parent)
{

    layout = new QGridLayout(this);
    QString value; //temporary value

    //handle comboBox
    comboBox = new QComboBox(this);

    actualizeMatrixSamples();
    connect(comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(comboBoxEdited(QString)));

    layout->addWidget(comboBox,0,0,1,3);

    matrix = new int*[3];
    for(int i=0;i<3;i++){
        matrix[i] = new int[3];
        for(int j=0;j<3;j++){
            value = (i==1 && j==1) ? "1" : "0";
            matrixWidget[i][j] = new QLineEdit(this);
            matrixWidget[i][j]->insert(value);
            matrixWidget[i][j]->setValidator( new QIntValidator(-255, 255, this) );
            matrixWidget[i][j]->setAlignment(Qt::AlignCenter);
            matrix[i][j] = matrixWidget[i][j]->text().toInt();

            connect(matrixWidget[i][j], SIGNAL(textChanged(QString)), this, SLOT(editMatrix()));

            layout->addWidget(matrixWidget[i][j],i+1,j);
        }
    }

    dividerLineEdit = new QLineEdit(this);
    dividerLineEdit->setText("1");
    dividerLineEdit->setAlignment(Qt::AlignCenter);
    layout->addWidget(dividerLineEdit,4,0,1,3);
    layout->setRowStretch(5,4);
    registerButton = new QPushButton("Register",this);
    layout->addWidget(registerButton, 6, 0, 1, 3);

    setLayout(layout);
    resize(150,200);


    connect(registerButton, SIGNAL(clicked()), this, SLOT(addEditMatrixSample()));

}



MatrixSelector::~MatrixSelector(){
    delete layout;
    delete[] matrix;
}


int** MatrixSelector::getMatrix(){
    return matrix;
}

int MatrixSelector::getDivider(){
    return dividerLineEdit->text().toInt();
}

void MatrixSelector::editMatrix(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            matrix[i][j] = matrixWidget[i][j]->text().toInt();
        }
    }
}

void MatrixSelector::comboBoxEdited(QString text){
    if(text == "Personnalisé"){
        int value;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                value = (i==1 && j==1) ? 1 : 0;
                matrixWidget[i][j]->setText(QString::number(value));
                matrix[i][j] = value;
            }
        }
        dividerLineEdit->setText("1");
        registerButton->setText("Register");
    }
    else{
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                matrixWidget[i][j]->setText(QString::number(std::get<0>(matrixSampleMap[text])[i][j]));
                matrix[i][j] = std::get<0>(matrixSampleMap[text])[i][j];
            }
        }
        dividerLineEdit->setText(QString::number(std::get<1>(matrixSampleMap[text])));
        registerButton->setText("Edit");
        registerButton->setEnabled(false);
    }

}

void MatrixSelector::actualizeMatrixSamples(){
    QFile file("ConvolutionMatrix.txt");
    disconnect(comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(comboBoxEdited(QString))); //required for clear the comboBox
    comboBox->clear();

    comboBox->addItem("Personnalisé");
    comboBox->insertSeparator(1);

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        QString temp;
        QString value;
        while(!stream.atEnd()){
            stream >> temp;
            std::get<0>(matrixSampleMap[temp]) = new int*[3];
            comboBox->addItem(temp);
            for(int i=0;i<3;i++){
                std::get<0>(matrixSampleMap[temp])[i] = new int[3];
                for(int j=0;j<3;j++){
                    stream >> value;
                    std::get<0>(matrixSampleMap[temp])[i][j] = value.toInt();
                }
            }
            stream >> value;
            std::get<1>(matrixSampleMap[temp]) = value.toInt();

        }

    }
    else{
        QMessageBox::information(0, "error", file.errorString());
    }
    connect(comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(comboBoxEdited(QString)));
    file.close();
}

void MatrixSelector::addEditMatrixSample(){


    QFile file("ConvolutionMatrix.txt");
    if(registerButton->text() == "Register"){

        if(file.open(QIODevice::Append)){
            bool ok;
            QString name = QInputDialog::getText(this, tr("name"), tr("name"),QLineEdit::Normal, QDir::home().dirName(), &ok);
            if (ok && !name.isEmpty()){
                QTextStream stream(&file);
                stream << endl << endl << name << '\n';
                for(int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        stream << matrixWidget[i][j]->text();
                        if(j!=2){
                            stream << " ";
                        }
                    }
                    stream << '\n';
                }
                stream << dividerLineEdit->text();
            }

        }else{
            QMessageBox::information(0, "error", file.errorString());
        }
    }
    file.close();
    actualizeMatrixSamples();
}
