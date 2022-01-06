#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtCharts>
#include <QList>
#include <QLabel>

QT_CHARTS_USE_NAMESPACE
#include <QMainWindow>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QList<QPointF> ReaddB(QString buf);
    QList<QPointF> ReadRI(QString buf);

    void SaveImage();


private slots:
    void on_OpenFileBtn_clicked();

    void on_SingleBtn_clicked();

    void on_MulBtn_clicked();

    void SaveSingleBtn_triggered();

    void SaveMulBtn_triggered();

    void on_mouseMovePoint(const QPointF &Point, bool state);

    void on_LegendMarkerClicked();

    void on_MaxSarch();

private:
    Ui::MainWindow *ui;

    QLabel *labXY;
    QLabel *mylab;
//    QLabel *peaklab;
    QLabel *peaklab = new QLabel();

    QChart* chart11 = new QChart();

    QChart* chart21 = new QChart();

    QChart* chart12 = new QChart();

    QChart* chart22 = new QChart();

    QChart* chart = new QChart();

    QAction *open = new QAction;
    QAction *savesingle = new QAction;
    QAction *savemul = new QAction;

    QList<QPointF>Points11;
    QList<QPointF>Points21;
    QList<QPointF>Points12;
    QList<QPointF>Points22;

    QList<double> point;

    QValueAxis *axisX, *axisY;

    qreal f0, f1;
    int count = 0;


};
#endif // MAINWINDOW_H
