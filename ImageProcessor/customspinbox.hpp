#ifndef CUSTOMSPINBOX_HPP
#define CUSTOMSPINBOX_HPP

#include <QSpinBox>
#include <QLabel>
#include <QHBoxLayout>
class customSpinBox : public QWidget
{
    Q_OBJECT

private:
    QLabel* label;
    QSpinBox* spinBox;
    QHBoxLayout* layout;

public:
    customSpinBox(QString text, QWidget* parent = nullptr);
    QSpinBox* getSpinBox();
    void setText(QString text);
};

#endif // CUSTOMSPINBOX_HPP
