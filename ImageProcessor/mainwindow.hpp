#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QImageReader>
#include <QDir>
#include <QDebug>
#include <QSpinBox>
#include <QFileDialog>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QTranslator>
#include <QResizeEvent>
#include "customspinbox.hpp"
#include "matrixselector.hpp"
#include "image.hpp"
#include "configdialog.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT //macro
private:
    QPushButton* generateImageBtn;
    QPushButton* prewittBtn;
    QPushButton* filterBtn;
    Image image;
    Image miniImage;
    QLabel* imageLabel;
    QLabel* miniImageLabel;
    customSpinBox* widthSpinBox;
    customSpinBox* heightSpinBox;
    MatrixSelector* ms;
    QWidget* m_mainWidget;
    QHBoxLayout* layout;
    QVBoxLayout* sideLayout;
    QProgressBar* progressBar;
    QMap<QString, QString> configMap;

    QVector<Image> imageHistory;
    int indexHistory;

    void reloadImage();
    void actualizeHistory();



private slots:
    void generateImage();
    void applyFilter();
    void prewitt();
    void saveImage();
    void openImage();
    void openConfiguration();
    void undo();
    void redo();


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_HPP

