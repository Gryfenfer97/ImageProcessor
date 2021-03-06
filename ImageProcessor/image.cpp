#include "image.hpp"

Image::Image() : QImage()
{
    ppt = new prewittProgressTransmitter;
}


Image::Image(int width, int height, int value) : QImage(width, height, QImage::Format_Grayscale8){
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            this->setPixel(j,i,qRgb(value,value,value));
        }
    }
}

Image::Image(int width, int height) : QImage(width, height, QImage::Format_Grayscale8){
    srand(time(NULL));
    int value;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            value = rand()%255;
            //value = (i+j)%256;
            this->setPixel(j,i,qRgb(value,value,value));
        }
    }
    ppt = new prewittProgressTransmitter();

}

Image::Image(const QImage& image) : QImage(image){
    ppt = new prewittProgressTransmitter;
}

Image::~Image(){

}

void Image::save(QString filename){
    if(filename.endsWith(".csv")){
        QFile file(filename);
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            for (int i = 0; i < this->height(); i++) {
                for (int j = 0; j < this->width(); j++) {
                    stream << this->pixelColor(i,j).blue();
                    if (j != this->width() - 1)
                        stream << ";";
                }
                stream << '\n';
            }
            file.close();
        }
    }
    else{
     QImage::save(filename);
    }
}


void Image::filter(int** mask, int divider, QString mode){
    int color;
    int progress = 0;
    if (divider == 0) {
        divider = getNormalizeDivider(mask);
    }
    if(mode == "Crop"){
        Image finalImage(width()-2, height()-2);
        int nbPixels = (width()-2)*(height()-2);
        for (int i = 1; i < height()-1; i++) {
            for (int j = 1; j < width()-1; j++) {
                if(divider > 0){
                    color = matrixConvolutionProduct(getRegion(i, j), mask)/divider;
                }
                else if(divider == 0){
                    color = (matrixConvolutionProduct(getRegion(i, j), mask) + 128)%256;
                }
                else{
                    color = ((matrixConvolutionProduct(getRegion(i, j), mask)/divider)+255)%256;
                }

                finalImage.setPixel(j-1,i-1, qRgb(color, color, color));
                progress++;
                ppt->emitPrewittProgress((int)((double)(progress*100)/(double)nbPixels));
            }
        }

        *this = finalImage;
        ppt->emitReset();
    }
    else{
        Image finalImage(width(), height());
        int nbPixels = width()*height();

        for (int i = 0; i < height(); i++) {
            for (int j = 0; j < width(); j++) {
                if(divider > 0){
                    color = matrixConvolutionProduct(getRegion(i, j), mask)/divider;
                }
                else if(divider == 0){
                    color = (matrixConvolutionProduct(getRegion(i, j), mask) + 128)%256;
                }
                else{
                    color = ((matrixConvolutionProduct(getRegion(i, j), mask)/divider)+255)%256;
                }

                finalImage.setPixel(j,i, qRgb(color, color, color));
                progress++;
                //qDebug() << progress;
                ppt->emitPrewittProgress((int)((double)(progress*100)/(double)nbPixels));
            }
        }
        *this = finalImage;
        ppt->emitPrewittProgress(0);
        ppt->emitReset();
    }


    ppt->emitReset();
    ppt->emitPrewittProgress(0);
    qDebug("filter applied");

}

int** Image::getRegion(int i, int j)
{
    int** region = new int* [3];
    int x, y;
    for (int k = 0; k < 3; k++) {
        region[k] = new int[3];
        for (int l = 0; l < 3; l++) {
            y = (((i + k - 1) % height()) + height()) % height();
            x = (((j + l - 1) % width()) + width()) % width();
            region[k][l] = qGray(pixel(x,y));
        }
    }

    return region;
}

int Image::matrixConvolutionProduct(int** region, int** mask)
{
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sum += region[i][j] * mask[i][j];
        }
    }

    return sum;
}

int Image::getNormalizeDivider(int** mask)
{
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sum += mask[i][j];
        }
    }
    return sum;
}

void Image::prewitt(){
    int** dGx = new int*[3];
    for(int i=0;i<3;i++){
        dGx[i] = new int[3];
        for(int j=-1;j<2;j++){
            dGx[i][j+1] = j;
        }
    }

    int** dGy = new int*[3];
    for(int i=0;i<3;i++){
        dGy[i] = new int[3];

    }
    for(int i=0;i<3;i++){
        for(int j=-1;j<2;j++){
            dGy[j+1][i] = j;
        }

    }

    Image G(*this);
    for (int y = 0; y < height(); y++) {
        for (int x = 0; x < width(); x++) {
            int Gx = matrixConvolutionProduct(getRegion(y,x), dGx);
            int Gy = matrixConvolutionProduct(getRegion(y,x), dGy);
            int color = sqrt(pow(Gx,2) + pow(Gy,2));
            G.setPixel(x,y,qRgb(color, color, color));
        }
    }
    *this = G;
}

prewittProgressTransmitter* Image::getPPT(){
    return ppt;
}

void Image::setPPT(){
    ppt = new prewittProgressTransmitter;
}
