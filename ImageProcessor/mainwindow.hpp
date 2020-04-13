#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QImageReader>
#include <QDir>
#include <QDebug>
//#include <QInputDialog>
#include <QSpinBox>
#include <QFileDialog>
//#include <QAction>
#include <QMenuBar>
#include "matrixselector.hpp"
#include "image.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT //macro
private:
    QPushButton* generateImageBtn;
    QPushButton* prewittBtn;
    Image image;
    QLabel* imageLabel;
    QSpinBox* widthSpinBox;
    QSpinBox* heightSpinBox;
    MatrixSelector* ms;
    QWidget* m_mainWidget;
    QGridLayout* layout;


    void reloadImage();



    QAction* write;


private slots:
    void generateImage();
    void prewitt();
    void saveImage();
    void openImage();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_HPP

