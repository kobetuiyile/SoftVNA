#include "marker.h"
#include "mainwindow.h"

Marker::Marker(QWidget *parent) : QChartView(parent)
{
    setMouseTracking(true);
    setDragMode(QGraphicsView::RubberBandDrag);
}

void Marker::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        chart()->zoom(1.2);
        break;
    case Qt::Key_Minus:
        chart()->zoom(0.8);
        break;
    case Qt::Key_Left:
        chart()->scroll(10, 0);
        chart()->zoom(0.99999999);
        break;
    case Qt::Key_Right:
        chart()->scroll(-10, 0);
        chart()->zoom(0.999999999);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, -10);
        chart()->zoom(0.9999999999);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, 10);
        chart()->zoom(0.99999999999);
        break;
    case Qt::Key_Home:
        chart()->zoomReset();
        break;
    default:QGraphicsView::keyPressEvent(event);
        break;

    }
}

void Marker::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        beginPoint = event->pos();
    }
    QChartView::mousePressEvent(event);
}

void Marker::mouseMoveEvent(QMouseEvent *event)
{
    QPoint Point = event->pos();
    emit mouseMovePoint(Point);
    QChartView::mouseMoveEvent(event);
}

void Marker::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        endPoint = event->pos();
        QRectF rect;
        rect.setTopLeft(beginPoint);
        rect.setBottomRight(endPoint);
        chart()->zoomIn(rect);
    }
    else if (event->button() == Qt::RightButton){
        chart()->zoomReset();
    }

    QChartView::mouseReleaseEvent(event);
}
