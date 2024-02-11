#include "mainwindow.h"
#include "./ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer;
    connect(timer, SIGNAL(timeout()), SLOT(update()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{

    QPainter painter;
    painter.begin(this);

    QBrush brush(Qt::darkGray);
    painter.setBrush(brush);
    painter.drawRect(rect());

    painter.translate(width()/2,height()/2);

    int R = 0.85 * qMin(width()/2, height()/2);
    QPen pen;
    pen.setWidth(3);


    for(int a = 0; a < 60; a++)
    {
        if (a % 5 == 0)
        {
            pen.setColor(Qt::black);
            painter.setPen(pen);
            painter.drawLine(0, R, 0, R-15);
        }
        else
        {
            pen.setColor(Qt::lightGray);
            painter.setPen(pen);
            painter.drawLine(0, R, 0, R-5);
        }
         painter.rotate(6.0);
    }

    QPoint hours_hand[3]
        {
            QPoint(14,16),
            QPoint(-14,16),
            QPoint(0,-100)
        };

    QPoint minutes_hand[3]
        {
            QPoint(12,14),
            QPoint(-12,14),
            QPoint(0,-150)
        };

    QPoint seconds_hand[3]
        {
            QPoint(10,12),
            QPoint(-10,12),
            QPoint(0,-220)
        };

    QTime time = QTime::currentTime();

    painter.save();

    pen.setColor(Qt::black);
    painter.setBrush(QColor(80,80,80));
    painter.setPen(pen);

    painter.rotate(30.0 *(time.hour() + time.minute()/60.0));
    painter.drawConvexPolygon(hours_hand, 3);

    painter.restore();
    painter.save();

    painter.setBrush(QColor(80,80,80));
    painter.setPen(pen);

    painter.rotate(6.0 * (time.minute() + time.second()/60.0));
    painter.drawConvexPolygon(minutes_hand, 3);

    painter.restore();
    painter.save();

    painter.setBrush(QColor(80,80,80));
    painter.setPen(pen);

    painter.rotate(6.0 * time.second());
    painter.drawConvexPolygon(seconds_hand, 3);

    painter.restore();

    painter.end();

}
