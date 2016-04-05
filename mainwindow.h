#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QListWidget>
#include "widget.h"
#include "videowidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QDockWidget *docwidget;
    QMediaPlayer *media;
    VideoWidget *video;
    Widget *wid;
    QMediaPlaylist *p;
    QListWidget *list;
protected:
    void keyPressEvent(QKeyEvent *event);
signals:

public slots:
    void playmedia();
    void stopmedia();
    void mute();
    void full();
    void updateduration();
    void addtoplaylist();
    void netxtrack();
    void prevtrack();
    void endofmedia();
    void replay();
    void curentmediachange(QModelIndex);
    //void SetWindowTitle(QMediaContent);
};

#endif // MAINWINDOW_H
