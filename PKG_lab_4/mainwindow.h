#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include "dialog.h"
#include "naivepoints.h"
#include "ddapoints.h"
#include "brspoirts.h"
#include "brcpoints.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void showBrCircle();
    void showBrSegment();
    void showNaive();
    void showDDA();
    void turnBack();
    void outOfRangeError();



public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);

    void setPoints(std::vector<QPointF> p) { points = p;}
    ~MainWindow();



private:
    Ui::MainWindow *ui;
    Dialog *d;
    NaivePoints naive;
    DdaPoints dda;
    BrsPoints brs;
    BrcPoints brc;

    std::vector<QPointF> points;

    pair<QPointF, QPointF> line;

    bool draw;

    QString text;




};
#endif // MAINWINDOW_H
