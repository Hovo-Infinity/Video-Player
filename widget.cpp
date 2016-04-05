#include "widget.h"
#include <QBoxLayout>
#include <QStyle>
#include <QWidgetAction>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    playlist=new QToolButton;
    playlist->setText("Add to playlist");
    time=new QLabel;
    play=new QToolButton;
    play->setAutoRaise(true);
    play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    play->setEnabled(false);
    stop=new QToolButton;
    stop->setAutoRaise(true);
    stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    stop->setEnabled(false);
    replay=new QToolButton;
    replay->setEnabled(false);
    replay->setCheckable(true);
    replay->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
    netx=new QToolButton;
    netx->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    netx->setAutoRaise(true);
    netx->setEnabled(false);
    prev=new QToolButton;
    prev->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    prev->setAutoRaise(true);
    prev->setEnabled(false);
    volume=new QToolButton;
    volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    volume->setPopupMode(QToolButton::MenuButtonPopup);
    tonext=new QToolButton;
    tonext->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
    tonext->setCheckable(true);
    tonext->setDisabled(true);
    vol=new QSlider(Qt::Horizontal);
    vol->setStatusTip("Volume");
    vol->setValue(100);
    vol->setMaximum(100);
    vol->setFixedSize(100,20);
    l=new QLabel;
    l->setText("100");
    l->setFixedSize(17,10);
    QBoxLayout *vl=new QHBoxLayout;
    vl->addWidget(vol);
    vl->addWidget(l);
    QWidget *volw=new QWidget;
    volw->setLayout(vl);
    QWidgetAction *act=new QWidgetAction(volume);
    act->setDefaultWidget(volw);
    volume->addAction(act);
    slider=new QSlider(Qt::Horizontal);
    QBoxLayout *hb=new QHBoxLayout;
    hb->addWidget(play);
    hb->addWidget(stop);
    hb->addWidget(prev);
    hb->addWidget(netx);
    hb->addWidget(replay);
    hb->addWidget(tonext);
    hb->addWidget(slider);
    hb->addWidget(time);
    hb->addWidget(volume);
    hb->addWidget(playlist);
    setLayout(hb);
}
Widget::~Widget()
{
    //media->stop();
    delete this;
}
