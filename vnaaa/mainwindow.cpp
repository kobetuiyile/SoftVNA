#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "marker.h"
#include <QFileDialog>
#include <QList>
#include <QDebug>
#include <cmath>
#include <QGridLayout>
#include <QGraphicsView>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("矢量网络分析仪软件分析版");

    QWidget *widgetmain = new QWidget;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(ui->widget_3, 0, 0);
    layout->addWidget(ui->widget_2, 0, 1);
    layout->addWidget(ui->widget, 0, 1);

    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 9);

    widgetmain->setLayout(layout);
    setCentralWidget(widgetmain);
    labXY = new QLabel("坐标X: Y:");
    labXY->setMinimumWidth(200);
    ui->statusbar->addWidget(labXY);

//    connect(ui->widget, &Marker::mouseMovePoint, this, &MainWindow::on_mouseMovePoint);
    connect(ui->SearchPeakBtn, &QPushButton::clicked, this, &MainWindow::on_MaxSarch);

    MainWindow::SaveImage();


}

void MainWindow::SaveImage(){
    QMenuBar *menubar = new QMenuBar;
    this->setMenuBar(menubar);
    QMenu *menufile = menubar->addMenu("文件");
    open = menufile->addAction("打开文件");
    connect(open,SIGNAL(triggered()), this, SLOT(on_OpenFileBtn_clicked()));
    QMenu *menusave = menufile->addMenu("保存图像");
    savesingle = menusave->addAction("单视窗图像");
    savemul = menusave->addAction("多视窗图像");
    connect(savesingle,SIGNAL(triggered()), this, SLOT(SaveSingleBtn_triggered()));
    connect(savemul,SIGNAL(triggered()), this, SLOT(SaveMulBtn_triggered()));

}



MainWindow::~MainWindow()
{
    delete ui;
}

QList<QPointF> MainWindow::ReadRI(QString buf){

    double logs11, logs21, logs12, logs22;

    if (buf.count('\t') > 5 && buf.count('#') == 0 && buf.count('!') == 0 && buf.size() > 5){

        logs11 = 20 * log10(sqrt(pow(buf.split('\t')[1].toDouble(), 2) + pow(buf.split('\t')[2].toDouble(), 2)));
        logs21 = 20 * log10(sqrt(pow(buf.split('\t')[3].toDouble(), 2) + pow(buf.split('\t')[4].toDouble(), 2)));
        logs12 = 20 * log10(sqrt(pow(buf.split('\t')[5].toDouble(), 2) + pow(buf.split('\t')[6].toDouble(), 2)));
        logs22 = 20 * log10(sqrt(pow(buf.split('\t')[7].toDouble(), 2) + pow(buf.split('\t')[8].toDouble(), 2)));

        Points11.append(QPointF(buf.split('\t')[0].toDouble(), logs11));
        Points21.append(QPointF(buf.split('\t')[0].toDouble(), logs21));
        Points12.append(QPointF(buf.split('\t')[0].toDouble(), logs12));
        Points22.append(QPointF(buf.split('\t')[0].toDouble(), logs22));
        point.append(logs11);
    }

    if (buf.count('\t') < 5 && buf.count('#') == 0 && buf.count('!') == 0 && buf.size() > 5){

        logs11 = 20 * log10(sqrt(pow(buf.split(' ')[1].toDouble(), 2) + pow(buf.split(' ')[2].toDouble(), 2)));
        logs21 = 20 * log10(sqrt(pow(buf.split(' ')[3].toDouble(), 2) + pow(buf.split(' ')[4].toDouble(), 2)));
        logs12 = 20 * log10(sqrt(pow(buf.split(' ')[5].toDouble(), 2) + pow(buf.split(' ')[6].toDouble(), 2)));
        logs22 = 20 * log10(sqrt(pow(buf.split(' ')[7].toDouble(), 2) + pow(buf.split(' ')[8].toDouble(), 2)));

        Points11.append(QPointF(buf.split(' ')[0].toDouble(), logs11));
        Points21.append(QPointF(buf.split(' ')[0].toDouble(), logs21));
        Points12.append(QPointF(buf.split(' ')[0].toDouble(), logs12));
        Points22.append(QPointF(buf.split(' ')[0].toDouble(), logs22));
        point.append(logs11);
    }
    return Points11;
    return Points21;
    return Points12;
    return Points22;

}

QList<QPointF> MainWindow::ReaddB(QString buf){


    if (buf.count('\t') > 5 && buf.count('#') == 0 && buf.count('!') == 0 && buf.size() > 5){
        Points11.append(QPointF(buf.split('\t')[0].toDouble(), buf.split('\t')[1].toDouble()));
        Points21.append(QPointF(buf.split('\t')[0].toDouble(), buf.split('\t')[3].toDouble()));
        Points12.append(QPointF(buf.split('\t')[0].toDouble(), buf.split('\t')[5].toDouble()));
        Points22.append(QPointF(buf.split('\t')[0].toDouble(), buf.split('\t')[7].toDouble()));
        point.append(buf.split('\t')[1].toDouble());
    }

    if (buf.count('\t') < 5 && buf.count('#') == 0 && buf.count('!') == 0 && buf.size() > 5){
        Points11.append(QPointF(buf.split(' ')[0].toDouble(), buf.split(' ')[1].toDouble()));
        Points21.append(QPointF(buf.split(' ')[0].toDouble(), buf.split(' ')[3].toDouble()));
        Points12.append(QPointF(buf.split(' ')[0].toDouble(), buf.split(' ')[5].toDouble()));
        Points22.append(QPointF(buf.split(' ')[0].toDouble(), buf.split(' ')[7].toDouble()));
        point.append(buf.split(' ')[1].toDouble());
    }
    return Points11;
    return Points21;
    return Points12;
    return Points22;

}

void MainWindow::on_MaxSarch(){

    peaklab->clear();
    double max = *std::max_element(point.begin(), point.end());
    int max_local= point.indexOf(max);
    peaklab->setParent(this);
    peaklab->setStyleSheet(QString("QLabel{color:#1564FF; font-family:\"Microsoft Yahei\"; font-size:12px; font-weight:bold;"
                                        " background-color:rgba(200, 100, 255, 51); border-radius:4px; text-align:center;}"));
    peaklab->setFixedSize(150, 50);
    peaklab->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    peaklab->setText(QString::asprintf("%.4fGHz, %.4fdB", (Points11[max_local].x() / pow(10, 9)), Points11[max_local].y()));
    ui->vswr->display((1 + pow(10, Points11[max_local].y() / 20)) / (1 - pow(10, Points11[max_local].y() / 20)));

    QPointF pos = chart->mapToPosition(Points11[max_local]);
    peaklab->move(pos.x(), pos.y() - peaklab->height() * 1);
    peaklab->setParent(ui->widget);
    peaklab->setVisible(true);
    if (count % 2 == 0){
        peaklab->setVisible(true);
        count++;
    }
    else{
        peaklab->clear();
        peaklab->setStyleSheet("background:transparent");
        ui->vswr->display("");
        count++;
    }

}


void MainWindow::on_OpenFileBtn_clicked()
{
    peaklab->hide();
    ui->vswr->display("");
    ui->lcdNumber->display("");

    QString filename = QFileDialog::getOpenFileName(this, "打开S2P文件", "");
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return;

    Points11.clear();
    Points21.clear();
    Points12.clear();
    Points22.clear();
    point.clear();

    chart11->removeAllSeries();
    chart21->removeAllSeries();
    chart12->removeAllSeries();
    chart22->removeAllSeries();

    chart->removeAllSeries();

    int c = 0;
    while (!file.atEnd()){

        QByteArray buff;
        buff = file.readLine();

        QString buf = QString(buff);

        if (buf.count('#') == 1 && buf.count('B') == 1){
            ui->lcdNumber->display(buf.split(' ').last());

            c = 1;
        }

        if (buf.count('#') == 1 && buf.count('I') == 1){
            ui->lcdNumber->display(buf.split(' ').last());

            c = 2;
        }

        if (c == 1){

            MainWindow::ReaddB(buf);
        }

        if (c == 2){

            MainWindow::ReadRI(buf);
        }

    }
    f0 = Points11.at(0).x();
    f1 = Points11.last().x();

}

void MainWindow::on_SingleBtn_clicked()
{
    ui->widget_2->hide();
    ui->widget->show();

    chart->removeAllSeries();

    QLineSeries *series11 = new QLineSeries();
    series11->append(Points11);

    QLineSeries *series21 = new QLineSeries();
    series21->append(Points21);

    QLineSeries *series12 = new QLineSeries();
    series12->append(Points12);

    QLineSeries *series22 = new QLineSeries();
    series22->append(Points22);

    chart->addSeries(series11);
    chart->addSeries(series21);
    chart->addSeries(series12);
    chart->addSeries(series22);

    series11->setName("S11");
    series21->setName("S21");
    series12->setName("S12");
    series22->setName("S22");

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).back()->setTitleText("Frequence");
    chart->axes(Qt::Horizontal).back()->setRange(f0, f1);
    chart->axes(Qt::Vertical).back()->setTitleText("dB");

    chart->axes(Qt::Horizontal).back()->setVisible(true);
    chart->axes(Qt::Vertical).back()->setVisible(true);


    ui->widget->setChart(chart);

    foreach (auto marker, ui->widget->chart()->legend()->markers()){
        connect(marker, &QLegendMarker::clicked, this, &MainWindow::on_LegendMarkerClicked);
    }

    connect(series11, &QLineSeries::hovered, this, &MainWindow::on_mouseMovePoint);
    connect(series21, &QLineSeries::hovered, this, &MainWindow::on_mouseMovePoint);
    connect(series12, &QLineSeries::hovered, this, &MainWindow::on_mouseMovePoint);
    connect(series22, &QLineSeries::hovered, this, &MainWindow::on_mouseMovePoint);
}

void MainWindow::on_MulBtn_clicked()
{
    peaklab->hide();
    ui->widget_2->show();
    ui->widget->hide();

    chart11->removeAllSeries();
    chart21->removeAllSeries();
    chart12->removeAllSeries();
    chart22->removeAllSeries();

    QLineSeries *series11 = new QLineSeries();
    series11->append(Points11);

    QLineSeries *series21 = new QLineSeries();
    series21->append(Points21);

    QLineSeries *series12 = new QLineSeries();
    series12->append(Points12);

    QLineSeries *series22 = new QLineSeries();
    series22->append(Points22);


    chart11->addSeries(series11);
    chart11->setTitle("S11");
    chart11->createDefaultAxes();
    chart11->axes(Qt::Horizontal).back()->setTitleText("Frequence");
    chart11->axes(Qt::Horizontal).back()->setRange(f0, f1);
    chart11->axes(Qt::Vertical).back()->setTitleText("dB");
    chart11->legend()->setVisible(false);
    ui->widget11->setChart(chart11);

    chart21->addSeries(series21);
    chart21->setTitle("S21");
    chart21->createDefaultAxes();
    chart21->axes(Qt::Horizontal).back()->setTitleText("Frequence");
    chart21->axes(Qt::Horizontal).back()->setRange(f0, f1);
    chart21->axes(Qt::Vertical).back()->setTitleText("dB");
    chart21->legend()->setVisible(false);
    ui->widget21->setChart(chart21);

    chart12->addSeries(series12);
    chart12->setTitle("S12");
    chart12->createDefaultAxes();
    chart12->axes(Qt::Horizontal).back()->setTitleText("Frequence");
    chart12->axes(Qt::Horizontal).back()->setRange(f0, f1);
    chart12->axes(Qt::Vertical).back()->setTitleText("dB");
    chart12->legend()->setVisible(false);
    ui->widget12->setChart(chart12);

    chart22->addSeries(series22);
    chart22->setTitle("S22");
    chart22->createDefaultAxes();
    chart22->axes(Qt::Horizontal).back()->setTitleText("Frequence");
    chart22->axes(Qt::Horizontal).back()->setRange(f0, f1);
    chart22->axes(Qt::Vertical).back()->setTitleText("dB");
    chart22->legend()->setVisible(false);
    ui->widget22->setChart(chart22);


}

void MainWindow::SaveSingleBtn_triggered(){

    QPixmap p = ui->widget->grab();
    QImage image = p.toImage();

    QString filename = QFileDialog::getSaveFileName(this,
        "保存单视窗图像",
        "",
        "PNG(*.png);; JPG(*.jpg);; GIF(*.GIF)");
    image.save(filename);

}

void MainWindow::SaveMulBtn_triggered(){

    QPixmap p = ui->widget_2->grab();
    QImage image = p.toImage();

    QString filename = QFileDialog::getSaveFileName(this,
        "保存多视窗图像",
        "",
        "PNG(*.png);; JPG(*.jpg);; GIF(*.GIF)");
    image.save(filename);

}

void MainWindow::on_mouseMovePoint(const QPointF &Point, bool state)
{

    if (state){

        float vswr = (1 + pow(10, Point.y() / 20)) / (1 - pow(10, Point.y() / 20));
        ui->vswr->display(vswr);

        labXY->setText(QString::asprintf("X=%.3fGHz,Y=%.4fdB", (Point.x() / pow(10, 9)), Point.y()));

        mylab = new QLabel(this);
        mylab->setStyleSheet(QString("QLabel{color:#1564FF; font-family:\"Microsoft Yahei\"; font-size:12px; font-weight:bold;"
                                            " background-color:rgba(21, 100, 255, 51); border-radius:4px; text-align:center;}"));
        mylab->setFixedSize(150, 50);
        mylab->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        mylab->setText(QString::asprintf("%.3fGHz, %.4fdB", (Point.x() / pow(10, 9)), Point.y()));
        QPoint curPos = mapFromGlobal(QCursor::pos());
        mylab->move(curPos.x() - mylab->width() / 2, curPos.y() - mylab->height() * 1.5);

        mylab->show();
    }
    else{
        ui->vswr->display("");
        mylab->hide();
    }

}

void MainWindow::on_LegendMarkerClicked()
{
    QLegendMarker *marker = (QLegendMarker *)sender();
    marker->series()->setVisible(!(marker->series()->isVisible()));
    marker->setVisible(true);

    qreal alpha = 1;
    if (!marker->series()->isVisible()){
        alpha = 0.5;
    }
    QBrush Brush = marker->labelBrush();
    QColor Color = Brush.color();
    Color.setAlphaF(alpha);
    Brush.setColor(Color);
    marker->setLabelBrush(Brush);
}

