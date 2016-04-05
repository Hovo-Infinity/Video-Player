#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QToolButton>
#include "videowidget.h"

class Widget : public QWidget
{
    Q_OBJECT
public:
    QSlider *vol,*slider;
    QToolButton *replay,*tonext;
    QToolButton *play,*stop,*volume,*playlist,*netx,*prev;
    QLabel *time,*l;
public:
    Widget(QWidget *parent = 0);
    ~Widget();

};

#endif // WIDGET_H
