#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H
#include <QVideoWidget>
#include <QMediaPlayer>

class VideoWidget : public QVideoWidget
{
public:
    VideoWidget(QWidget *parent=0);
public slots:
    void ShowContextMenu(const QPoint &);
protected:
    void mouseDoubleClickEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*);
};

#endif // VIDEOWIDGET_H
