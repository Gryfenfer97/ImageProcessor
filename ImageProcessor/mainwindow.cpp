#include "mainwindow.hpp"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("ImageProcessor");

    m_mainWidget = new QWidget(this);
    layout = new QHBoxLayout(m_mainWidget);
    sideLayout = new QVBoxLayout;
    this->setMinimumSize(675,560);

    progressBar = new QProgressBar();
    progressBar->setRange(0,100);

    generateImageBtn = new QPushButton(tr("&Generate Image"),this);
    prewittBtn = new QPushButton("Prewitt", this);

    widthSpinBox = new customSpinBox(tr("width : "), this);
    heightSpinBox = new customSpinBox(tr("height : "),this);

    widthSpinBox->getSpinBox()->setMaximum(850);
    widthSpinBox->getSpinBox()->setValue(500);
    heightSpinBox->getSpinBox()->setMaximum(850);
    heightSpinBox->getSpinBox()->setValue(500);

    imageLabel = new QLabel(this);
    indexHistory=-1;
    image = Image(500,500);
    actualizeHistory();
    imageLabel->setMaximumSize(800,800);
    imageLabel->setScaledContents(true);


    layout->addStretch(5);
    layout->addWidget(imageLabel);
    layout->addStretch(5);


    ms = new MatrixSelector(this);
    ms->setFixedSize(150,200);



    miniImage = image;
    miniImageLabel = new QLabel(this);
    miniImageLabel->setScaledContents(true);


    sideLayout->addStretch(1);

    sideLayout->addWidget(miniImageLabel);
    sideLayout->addWidget(widthSpinBox);
    sideLayout->addWidget(heightSpinBox);
    sideLayout->addWidget(generateImageBtn);
    sideLayout->addStretch(1);
    sideLayout->addWidget(ms);
    sideLayout->addStretch(1);
    sideLayout->addWidget(prewittBtn);
    sideLayout->addWidget(progressBar);
    sideLayout->addStretch(1);


    layout->addStretch(5);
    layout->addLayout(sideLayout);
    layout->addStretch(1);

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
    fileMenu->addAction(tr("&Configuration"), this, &MainWindow::openConfiguration);
    QMenu *editionMenu = menuBar()->addMenu(tr("&Edition"));
    QAction* undo = editionMenu->addAction(tr("&Undo"), this, &MainWindow::undo);
    undo->setShortcut(tr("Ctrl+Z"));
    QAction* redo = editionMenu->addAction(tr("&Redo"), this, &MainWindow::redo);
    redo->setShortcut(tr("Ctrl+Y"));

    connect(generateImageBtn, SIGNAL(clicked(bool)), this, SLOT(generateImage()));
    connect(prewittBtn, SIGNAL(clicked(bool)), this, SLOT(prewitt()));
    connect(image.getPPT(), SIGNAL(prewittProgress(int)), progressBar, SLOT(setValue(int)));
    connect(image.getPPT(), SIGNAL(reset()), progressBar, SLOT(reset()));

    m_mainWidget->setLayout(layout);
    setCentralWidget(m_mainWidget);

    configMap = ConfigDialog::loadConfig();
    ms->setMatrixPath(configMap["MatrixPath"]);


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
    imageLabel->setMaximumSize(image.width(),image.height());

    miniImageLabel->setPixmap(QPixmap::fromImage(miniImage));
    miniImageLabel->setMaximumSize(150,150*image.height()/image.width());
    connect(image.getPPT(), SIGNAL(prewittProgress(int)), progressBar, SLOT(setValue(int)));
    connect(image.getPPT(), SIGNAL(reset()), progressBar, SLOT(reset()));
    qDebug() << "reloaded";

}

void MainWindow::prewitt(){
    image.prewitt(ms->getMatrix(), ms->getDivider(), configMap["Mode"]);
    actualizeHistory();
    reloadImage();

}

void MainWindow::generateImage(){
    qDebug() << "Image generated";
    image = Image(widthSpinBox->getSpinBox()->value(),heightSpinBox->getSpinBox()->value());
    miniImage = image;
    actualizeHistory();
    reloadImage();
    this->setWindowTitle("ImageProcessor");
}

void MainWindow::saveImage(){
    QFileDialog dialog(this, tr("Save File As"), "..", tr("Image Files (*.png *.jpg *.bmp *.ppm)"));
    QString filename;
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if(dialog.exec()){
        filename = dialog.selectedFiles().first();
    }
    QImageWriter writer(filename);
    writer.write(image);


}

void MainWindow::openImage(){
     QFileDialog dialog(this, tr("Open Image"), "..", tr("Image Files (*.png *.jpg *.bmp *.ppm)"));
     QString filename;
     if(dialog.exec()){
         qDebug() <<"Image from : " <<dialog.selectedFiles().first() << " opened";
         filename = dialog.selectedFiles().first();
         QImageReader reader(filename);
         image = QImage(reader.read());
         image = image.scaled(image.width(), image.height(),Qt::KeepAspectRatio);
         image.setPPT();
         connect(image.getPPT(), SIGNAL(prewittProgress(int)), progressBar, SLOT(setValue(int)));
         connect(image.getPPT(), SIGNAL(reset()), progressBar, SLOT(reset()));
         int** identity = new int*[3];
         int value;
         for(int i=0;i<3;i++){
             identity[i] = new int[3];
             for(int j=0;j<3;j++){
                 value = (i==1 && j==1) ? 1 : 0;
                 identity[i][j] = value;
             }
         }

        image.prewitt(identity,1);
         miniImage = image;
         actualizeHistory();
         reloadImage();
        setWindowTitle("ImageEncoder | " + filename);
     }
}

void MainWindow::undo(){
    if(indexHistory>0){
        indexHistory--;
        image = imageHistory[indexHistory];
         miniImage = image;
         reloadImage();

    }
}

void MainWindow::redo(){
    if(indexHistory<imageHistory.size()-1){
        indexHistory++;
        image = imageHistory[indexHistory];
         miniImage = image;
        reloadImage();

    }
}

void MainWindow::actualizeHistory(){
    while(indexHistory<imageHistory.size()-1){
        imageHistory.pop_back();
    }
    imageHistory.push_back(image);
    indexHistory++;
}

void MainWindow::openConfiguration(){
    ConfigDialog qd;
    if(qd.exec()){
        configMap = qd.getConfigMap();
        ms->setMatrixPath(configMap["MatrixPath"]);
    }
}

