#ifndef FANCYSLIDER_H
#define FANCYSLIDER_H

#include <QSlider>
#include <QMouseEvent>

class FancySlider : public QSlider
{
    Q_OBJECT
public:
    explicit FancySlider(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *e);

signals:
    void playbackPosChanged(qint64 value);

public slots:
//    void valueChanged(int value);

};

#endif // FANCYSLIDER_H
