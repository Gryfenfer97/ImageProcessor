#include "mainwindow.hpp"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("ImageEncoder");

    //m_mainWidget = new QWidget(this);
    this->setMinimumSize(400,400);

    generateImageBtn = new QPushButton("Generate Image",this);
    generateImageBtn->move(10,25);
    prewittBtn = new QPushButton("Prewitt", this);
    prewittBtn->move(450,25);

    widthSpinBox = new QSpinBox(this);
    widthSpinBox->move(150,25);
    heightSpinBox = new QSpinBox(this);
    heightSpinBox->move(300,25);

    widthSpinBox->setMaximum(850);
    widthSpinBox->setValue(500);
    heightSpinBox->setMaximum(850);
    heightSpinBox->setValue(500);
    QDir directory("../ImageProcessor/");
    directory.makeAbsolute();



    imageLabel = new QLabel(this);
    image = Image(500,500);
    imageLabel->setMaximumSize(1000,800);
    imageLabel->setScaledContents(true);


    ms = new MatrixSelector(this);

    reloadImage();

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction* open = fileMenu->addAction(tr("&Open"), this, &MainWindow::openImage);
    open->setShortcut(tr("Ctrl+O"));
    QAction* generate = fileMenu->addAction(tr("&Generate"), this, &MainWindow::generateImage);
    generate->setShortcut(tr("Ctrl+N"));
    QAction* save = fileMenu->addAction(tr("&Save"), this, &MainWindow::saveImage);
    save->setShortcut(tr("Ctrl+S"));
    QAction* reload = fileMenu->addAction(tr("&Actualize"), this, &MainWindow::reloadImage);
    reload->setShortcut(tr("F5"));


    connect(generateImageBtn, SIGNAL(clicked(bool)), this, SLOT(generateImage()));
    connect(prewittBtn, SIGNAL(clicked(bool)), this, SLOT(prewitt()));
}

MainWindow::~MainWindow()
{
    delete generateImageBtn;
    delete imageLabel;
    delete widthSpinBox;
    delete heightSpinBox;
}

void MainWindow::reloadImage(){
    imageLabel->setPixmap(QPixmap::fromImage(image));

    imageLabel->resize(image.width(),image.height());
    if(image.width()+100 > 500){
        this->setMinimumSize(imageLabel->width()+100 + 150,imageLabel->height()+150);
        this->setMaximumSize(imageLabel->width()+100 + 150,imageLabel->height()+150);
        ms->move(imageLabel->width()+70,this->height()/2 - ms->height()/2);
    }
    else{
        this->setMaximumSize(500 + 150,imageLabel->height()+150);
        this->setMinimumSize(500 + 150,imageLabel->height()+150);
        ms->move(500,this->height()/2 - ms->height()/2);
    }
    imageLabel->move((width()-imageLabel->width())/2 - 90/*- ms->width()*/, (height()-imageLabel->height())/2);
    qDebug() << "reloaded";

}

void MainWindow::prewitt(){
    image.prewitt(ms->getMatrix(), ms->getDivider());
    reloadImage();

}

void MainWindow::generateImage(){
    qDebug() << "click click";
    image = Image(widthSpinBox->value(),heightSpinBox->value());
    reloadImage();
}

void MainWindow::saveImage(){
    QFileDialog dialog(this, tr("Save File As"));
    QString filename;
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if(dialog.exec()){
        qDebug() << dialog.selectedFiles().first();
        filename = dialog.selectedFiles().first();
    }
    QImageWriter writer(filename);
    writer.write(image);

}

void MainWindow::openImage(){
     QFileDialog dialog(this, tr("Open Image"));
     QString filename;
     if(dialog.exec()){
         qDebug() << dialog.selectedFiles().first();
         filename = dialog.selectedFiles().first();
         QImageReader reader(filename);
         image = QImage(reader.read());
         reloadImage();
        setWindowTitle("ImageEncoder | " + filename);
     }

}
