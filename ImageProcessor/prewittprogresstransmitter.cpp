#include "prewittprogresstransmitter.hpp"

prewittProgressTransmitter::prewittProgressTransmitter(QWidget *parent) : QWidget(parent)
{

}


void prewittProgressTransmitter::emitPrewittProgress(int progress){
    emit prewittProgress(progress);
}

void prewittProgressTransmitter::emitReset(){
    emit reset();
}
