#ifndef PREWITTPROGRESSTRANSMITTER_HPP
#define PREWITTPROGRESSTRANSMITTER_HPP

#include <QObject>
#include <QWidget>
#include <QDebug>


class prewittProgressTransmitter : public QWidget
{
    Q_OBJECT
public:
    explicit prewittProgressTransmitter(QWidget *parent = nullptr);
    void emitPrewittProgress(int progress);
    void emitReset();

signals:
    void prewittProgress(int);
    void reset();
};

#endif // PREWITTPROGRESSTRANSMITTER_HPP
