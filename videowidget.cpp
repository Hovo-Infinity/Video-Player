#include "videowidget.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QBoxLayout>
#include <QMenu>

VideoWidget::VideoWidget(QWidget *parent)
    : QVideoWidget(parent)
{
    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::black);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setPalette(p);
}
void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    setFullScreen(!isFullScreen());
    event->accept();
}
void VideoWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape)
    {
        setFullScreen(false);
        event->accept();
    }
    if(event->key() == Qt::Key_Enter && event->modifiers() && Qt::Key_Alt)
    {
        setFullScreen(!isFullScreen());
        event->accept();
    }
}
