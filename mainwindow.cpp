#include "mainwindow.h"
#include "videowidget.h"
#include <QKeyEvent>
#include <QStyle>
#include <QSlider>
#include <QWidgetAction>
#include <QFileDialog>
#include <QLabel>
#include <QBoxLayout>
#include <QScrollBar>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    video=new VideoWidget;
    wid=new Widget;
    /*docwidget=new QDockWidget("Controlers",this);
    docwidget->setWidget(wid);
    docwidget->setFloating(false);
    addDockWidget(Qt::BottomDockWidgetArea,docwidget);*/
    list=new QListWidget;
    media=new QMediaPlayer;
    video=new VideoWidget;
    connect(wid->play,SIGNAL(clicked(bool)),this,SLOT(playmedia()));
    connect(wid->stop,SIGNAL(clicked(bool)),this,SLOT(stopmedia()));
    connect(wid->volume,SIGNAL(clicked(bool)),this,SLOT(mute()));
    connect(wid->vol,SIGNAL(valueChanged(int)),media,SLOT(setVolume(int)));
    connect(wid->vol,SIGNAL(valueChanged(int)),wid->l,SLOT(setNum(int)));
    connect(wid->vol,SIGNAL(valueChanged(int)),media,SLOT(setVolume(int)));
    connect(media,&QMediaPlayer::durationChanged,wid->slider,&QSlider::setMaximum);
    connect(wid->slider,&QSlider::sliderMoved,media,&QMediaPlayer::setPosition);
    connect(wid->slider,&QSlider::valueChanged,this,&MainWindow::endofmedia);
    connect(media,&QMediaPlayer::positionChanged,wid->slider,&QSlider::setValue);
    connect(media,&QMediaPlayer::positionChanged,this,&MainWindow::updateduration);
    connect(wid->netx,&QToolButton::clicked,this,&MainWindow::netxtrack);
    connect(wid->prev,&QToolButton::clicked,this,&MainWindow::prevtrack);
    connect(wid->replay,&QToolButton::clicked,this,&MainWindow::replay);
    connect(list,SIGNAL(activated(QModelIndex)),this,SLOT(curentmediachange(QModelIndex)));
    //connect(media,SIGNAL(mediaChanged(QMediaContent)),this,SLOT(SetWindowTitle(QMediaContent)));
    p=new QMediaPlaylist;
    connect(wid->playlist,&QToolButton::clicked,this,&MainWindow::addtoplaylist);
    media->setVideoOutput(video);
    QScrollBar *scrol1=new QScrollBar;
    list->addScrollBarWidget(scrol1,Qt::AlignBottom);
    QScrollBar *scrol2=new QScrollBar;
    list->addScrollBarWidget(scrol2,Qt::AlignBottom);
    QWidget *W=new QWidget;
    QBoxLayout *hb=new QHBoxLayout;
    hb->addWidget(video, 2);
    hb->addWidget(list);
    QBoxLayout *vb=new QVBoxLayout;
    vb->addLayout(hb);
    vb->addWidget(wid);
    W->setLayout(vb);
    setCentralWidget(W);
    QSize Size;
    Size.setWidth(200);
    Size.setHeight(100);
    setMinimumSize(video->size()+Size);
    setWindowIcon(QIcon(tr(":/Multimedia 1.ico")));
}
MainWindow::~MainWindow()
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
     if(event->key()==Qt::Key_Alt)
             docwidget->setHidden(!docwidget->isHidden());
}
/*void MainWindow::openfile()
{
    QString str=QFileDialog::getOpenFileName(this,tr("Open File"),QDir::homePath(),
                                             tr("Music(*.mp3);;Video Files(*.mp4);;All Files(*.*)")
                                             );
    media->setMedia(QUrl::fromLocalFile(str));
    media->play();
    if(media->state()==QMediaPlayer::PlayingState)
    {
        wid->play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        wid->play->setEnabled(true);
        wid->stop->setEnabled(true);
        wid->netx->setEnabled(true);
        wid->prev->setEnabled(true);
        wid->replay->setEnabled(true);
    }
}*/
void MainWindow::playmedia()
{
    wid->play->setEnabled(true);
    wid->stop->setEnabled(true);
    if(media->state() == QMediaPlayer::PlayingState)
       {
        media->pause();
        wid->play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
    else
    {
        media->play();
        wid->play->setIcon(style()->standardIcon((QStyle::SP_MediaPause)));
    }
}
void MainWindow::stopmedia()
{
    media->stop();
    wid->stop->setEnabled(false);
    wid->play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}
void MainWindow::mute()
{
    if(media->isMuted())
    {
        wid->volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        media->setMuted(false);
    }
    else
    {
        wid->volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        media->setMuted(true);
    }
}
void MainWindow::full()
{
    video->setFullScreen(true);
}
void MainWindow::updateduration()
{
    QString timestr,str;
    str.setNum(media->position()/60000/60);
    if(str.length()<2)
        timestr+='0';
    timestr+=str+':';
    str.setNum(media->position()/60000%60);
    if(str.length()<2)
        timestr+='0';
    timestr+=str+':';
    str.setNum(media->position()%60000/1000);
    if(str.length()<2)
        timestr+='0';
    timestr+=str;
    wid->time->setText(timestr);
}
void MainWindow::addtoplaylist()
{
    QString str=QFileDialog::getOpenFileName(this,tr("Open File"), QDir::homePath(),
                                             tr("Music(*.mp3);;Video Files(*.mp4);;All Files(*.*)")
                                             );
    list->addItem(str);
    p->addMedia(QUrl::fromLocalFile(str));
    wid->netx->setEnabled(true);
    wid->prev->setEnabled(true);
    wid->replay->setEnabled(true);
    wid->tonext->setEnabled(true);
    if(media->state()!=QMediaPlayer::PlayingState)
    {
        p->setCurrentIndex(0);
        list->setCurrentRow(0);
        media->setMedia(p->currentMedia());
        playmedia();
    }
}
void MainWindow::netxtrack()
{
    p->setCurrentIndex(p->nextIndex());
    list->setCurrentRow(list->currentRow()+1);
    media->setMedia(p->currentMedia());
    media->play();
}
void MainWindow::prevtrack()
{
    p->setCurrentIndex(p->previousIndex());
    list->setCurrentRow(list->currentRow()-1);
    media->setMedia(p->currentMedia());
    media->play();
}
void MainWindow::endofmedia()
{
    if(wid->tonext->isChecked())
    {
        if(wid->slider->value()==wid->slider->maximum())
            this->netxtrack();
        if(p->currentMedia().isNull())
            netxtrack();
    }
}
void MainWindow::replay()
{
    if(wid->replay->isChecked())
    {
        int i=p->currentIndex();
        if(wid->slider->value()==wid->slider->maximum())
        {
            p->setCurrentIndex(i);
            media->setMedia(p->currentMedia());
            playmedia();
        }
    }
}
void MainWindow::curentmediachange(QModelIndex index)
{
    list->setCurrentIndex(index);
    p->setCurrentIndex(list->currentRow());
    media->setMedia(p->currentMedia());
    media->play();
    QString str=media->metaData("Author").toString();
    qDebug()<<str;
}
/*void MainWindow::SetWindowTitle(QMediaContent content)
{

}*/
