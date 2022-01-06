#ifndef MARKER_H
#define MARKER_H

#include <QWidget>
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE
#include <QPoint>


class Marker : public QChartView
{
    Q_OBJECT

public:
    explicit Marker(QWidget *parent = nullptr);

private:

    QPoint beginPoint;
    QPoint endPoint;

protected:

    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:

    void mouseMovePoint(QPoint Point);

};

#endif // MARKER_H
