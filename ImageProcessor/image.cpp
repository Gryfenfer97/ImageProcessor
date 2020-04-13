#include "image.hpp"

Image::Image() : QImage()
{

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
            //value = (j*j)%256;
            this->setPixel(j,i,qRgb(value,value,value));
        }
    }

}

Image::Image(const QImage& image) : QImage(image){

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


void Image::prewitt(int** mask, int divider){
    Image finalImage(width(), height());
    int color;
    if (divider == 0) {
        divider = getNormalizeDivider(mask);
    }
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

        }
    }
    qDebug("filter applied");
    *this = finalImage;
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
