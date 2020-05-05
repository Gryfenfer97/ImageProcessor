#ifndef MATRIXSELECTOR_HPP
#define MATRIXSELECTOR_HPP

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QIntValidator>
#include <QDebug>
#include <QComboBox>
#include <QFile>
#include <QMap>
#include <QMessageBox>
#include <QInputDialog>
#include <QDir>

class MatrixSelector : public QWidget
{
    Q_OBJECT
private:
    QGridLayout* layout;
    QComboBox* comboBox;
    QLineEdit* matrixWidget[3][3];
    QLineEdit* dividerLineEdit;
    int** matrix;
    QMap<QString, std::tuple<int**, int>> matrixSampleMap;

    QPushButton* registerButton;

    QString matrixPath;

private slots:
    void editMatrix();
    void comboBoxEdited(QString);
    void addEditMatrixSample();


public:
    explicit MatrixSelector(QWidget *parent = nullptr);
    ~MatrixSelector();

    int** getMatrix();
    int getDivider();
    void actualizeMatrixSamples();
    void setMatrixPath(QString filename);
};

#endif // MATRIXSELECTOR_HPP
