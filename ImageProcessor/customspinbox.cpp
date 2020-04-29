#include "customspinbox.hpp"

customSpinBox::customSpinBox(QString text, QWidget* parent) : QWidget(parent)
{
    layout = new QHBoxLayout(this);
    label = new QLabel(text, this);
    spinBox = new QSpinBox(this);
    layout->addWidget(label);
    layout->addWidget(spinBox);
    layout->setStretch(1,1);
}

QSpinBox* customSpinBox::getSpinBox(){
    return spinBox;
}

void customSpinBox::setText(QString text){
    label->setText(text);
}
