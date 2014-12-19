#include "fancyslider.h"

FancySlider::FancySlider(QWidget *parent) :
    QSlider(parent)
{
//    connect(this, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));

}

//From http://stackoverflow.com/a/11133022
void FancySlider::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        setValue(minimum() + ((maximum()-minimum()) * e->x()) / width());
    }

    e->accept();
    QSlider::mousePressEvent(e);

    emit playbackPosChanged((qint64)this->value());
}

//void FancySlider::valueChanged(int value)
//{
////    qint64 val = value / 10.0;


//}
