#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <QImage>
#include <QImageWriter>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class Image : public QImage
{
private:
    int** getRegion(int i, int j);
    int matrixConvolutionProduct(int** region, int** mask);
    int getNormalizeDivider(int** mask);
public:
    Image();
    Image(int width, int height, int value);
    Image(int width, int height);
    Image(const QImage& image);

    ~Image();

    void prewitt(int** mask, int divider);

    void save(QString filename);

};

#endif // IMAGE_HPP
