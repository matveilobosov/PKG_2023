#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

const int cellw = 40;
const int cellh = 30;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->brc, SIGNAL(clicked()), this, SLOT(showBrCircle()));
    connect(ui->brs, SIGNAL(clicked()), this, SLOT(showBrSegment()));
    connect(ui->naive, SIGNAL(clicked()), this, SLOT(showNaive()));
    connect(ui->dda, SIGNAL(clicked()), this, SLOT(showDDA()));
    connect(ui->back, SIGNAL(clicked()), this, SLOT(turnBack()));

    draw = 0;
    ui->back->hide();


    setFixedSize(800,540);


}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::outOfRangeError(){
    QMessageBox::information(NULL,QObject::tr("Warning"),tr("Segment or circle will be out of coordinate plane"));
}


void MainWindow::showBrCircle(){

    setMinimumSize(800,540);
    setMaximumSize(4000,2700);
    QPointF p0;
    int radius;
    d = new Dialog(circle);
    while(true){
        if(d->exec()==QDialog::Accepted){
            radius = d->getRadius();
            p0 = d->getP0();
        }else{
            ui->label->setText("Choose algorithm");
            return;
        }
        if(qAbs(p0.x()) + qAbs(radius) >= cellw/2|| qAbs(p0.y()) + qAbs(radius) >= cellh/2)
        {
            outOfRangeError();
        }else{
            break;
        }
    }

    ui->brc->hide();
    ui->brs->hide();
    ui->dda->hide();
    ui->naive->hide();
    ui->back->show();

    brc = BrcPoints(p0.x(), p0.y(),radius);
    brc.setPoints(p0.x(), p0.y(),radius);

    line = {QPointF(-cellw,-cellh),QPointF(-cellw, -cellh)};


    points = brc.getPoints();

    draw =1;


    ui->label->setText("Bresenham's circle Algorithm");
    //ui->label->setText(QString::number(points.size()));
}

void MainWindow::showBrSegment(){

    setMinimumSize(800,540);
    setMaximumSize(4000,2700);
    QPointF p0;
    QPointF p1;
    d = new Dialog(segment);
    while(true){
        if(d->exec()==QDialog::Accepted){
            p1 = d->getP1();
            p0 = d->getP0();
        }else{
            ui->label->setText("Choose algorithm");
            return;
        }
        if(qAbs(p0.x()) >= cellw/2 || qAbs(p0.y()) >= cellh/2 || qAbs(p1.x()) >= cellw/2 || qAbs(p1.y()) >= cellh/2){
            outOfRangeError();
        }else{
            break;
        }
    }
    ui->brc->hide();
    ui->brs->hide();
    ui->dda->hide();
    ui->naive->hide();
    ui->back->show();


    brs.setPoints(p0.x(),p1.x(), p0.y(),p1.y());

    line = {p0,p1};

    points = brs.getPoints();

    draw =1;

    ui->label->setText("Bresenham's segment Algorithm");
}

void MainWindow::showNaive(){

    setMinimumSize(800,540);
    setMaximumSize(4000,2700);

    QPointF p0;
    QPointF p1;
    d = new Dialog(segment);
    while(true){
        if(d->exec()==QDialog::Accepted){
            p1 = d->getP1();
            p0 = d->getP0();
        }else{
            ui->label->setText("Choose algorithm");
            return;
        }
        if(qAbs(p0.x()) >= cellw/2 || qAbs(p0.y()) >= cellh/2 || qAbs(p1.x()) >= cellw/2 || qAbs(p1.y()) >= cellh/2){
            outOfRangeError();
        }else{
            break;
        }
    }
    ui->brc->hide();
    ui->brs->hide();
    ui->dda->hide();
    ui->naive->hide();
    ui->back->show();

    naive.setPoints(p0.x(),p1.x(), p0.y(),p1.y());

    line = {p0,p1};

    points = naive.getPoints();

    draw =1;


    ui->label->setText("Naive algorithm");
}

void MainWindow::showDDA(){

    setMinimumSize(800,540);
    setMaximumSize(4000,2700);
    QPointF p0;
    QPointF p1;

    d = new Dialog(segment);
    while(true){
        if(d->exec()==QDialog::Accepted){
            p1 = d->getP1();
            p0 = d->getP0();
        }else{
            ui->label->setText("Choose algorithm");
            return;
        }
        if(qAbs(p0.x()) >= cellw/2 || qAbs(p0.y()) >= cellh/2 || qAbs(p1.x()) >= cellw/2 || qAbs(p1.y()) >= cellh/2){
            outOfRangeError();
        }else{
            break;
        }
    }
    ui->brc->hide();
    ui->brs->hide();
    ui->dda->hide();
    ui->naive->hide();
    ui->back->show();

    dda.setPoints(p0.x(),p1.x(), p0.y(),p1.y());



    line = {p0,p1};
    points = dda.getPoints();
    draw =1;


    ui->label->setText("DDA algorithm");
}



void MainWindow::paintEvent(QPaintEvent* e)
{
    QPainter p(this);

    p.setFont(QFont("Arial", 10));

    if(!draw)
    {
        p.eraseRect(e->rect());
        ui->label->setFixedWidth(this->width());
       // ui->naive->setGeometry(this->width()/2-110,140,361,51);
    }
    else
    {

     ui->label->setFixedWidth(this->width());
        ui->back->setGeometry(this->width()-160,20,121,31);
    double h = this->height();
    double w = this->width();
    p.translate(w/2,h/2);
    p.fillRect(-1*w/2,-1*h/2+60, w, h-120, Qt::white);


     double sizex = w/cellw;
     double sizey = (h-120)/cellh;


     double curx =-1*w/2;
     p.setPen(QPen(Qt::lightGray,1));
     for(int i=0;i<=cellw;i++)
     {
            p.drawLine(curx, -1*h/2+60,curx,h/2-60);
              p.setPen(QPen(Qt::black,2));
            p.setFont(QFont("Arial", 8));
            if(i == cellw/2) p.drawText(QRect(curx-20+sizex,5,40,40), Qt::AlignCenter, "1");
              p.setPen(QPen(Qt::lightGray,1));
            curx+=sizex;
     }
    double cury = -1*h/2+60;
     for(int i=0;i<=cellh;i++)
     {
            p.drawLine(-1*w/2,cury,w/2,cury);
            p.setPen(QPen(Qt::black,2));
            p.setFont(QFont("Arial", 8));
            if(i == cellh/2) p.drawText(QRect(-35,cury-20-sizey,40,40), Qt::AlignCenter, "1");
              p.setPen(QPen(Qt::lightGray,1));
            cury+=sizey;
     }

     for(int i=0;i<points.size();i++)
     {
            p.fillRect(points[i].rx()*sizex, -1*(points[i].ry()*sizey+sizey),sizex, sizey, Qt::green);
            p.translate(points[i].rx()*sizex, -1*points[i].ry()*sizey);
            p.setBrush(QBrush(Qt::black));
            p.drawEllipse(-sizex/8,-sizex/8,sizex/4,sizex/4);
            p.translate(-1*points[i].rx()*sizex, points[i].ry()*sizey);

     }
     p.setPen(QPen(Qt::black, 3));
     p.drawLine(-1*w/2+5,0,w/2-5,0);
     p.drawLine(-sizex/4,-sizey,sizex/4,-sizey);

     p.drawLine(sizex,-sizey/4,sizex,sizey/4);

     p.translate(w/2-5,0);
p.setFont(QFont("Arial", 10));
     p.drawText(QRect(-40,-40,40,40), Qt::AlignCenter, "x");
     p.drawLine(-5,5,0,0);
     p.drawLine(-5,-5,0,0);
     p.translate(-1*w/2+5,0);
     p.drawLine(0,-1*h/2+65,0,h/2-65);
     p.translate(0,-1*h/2+65);
     p.drawLine(-5,5,0,0);
     p.drawLine(5,5,0,0);
     p.drawText(QRect(10,0,40,40), Qt::AlignCenter, "y");
     p.translate(0,h/2-65);
     p.setPen(QPen(Qt::black, 2));
     p.setBrush(QBrush(Qt::black, Qt::NoBrush));

      p.setFont(QFont("Arial", 8));
     if(line.first.x()!=-cellw)
     {

            p.drawLine(line.first.x()*sizex,-1*line.first.y()*sizey, line.second.x()*sizex,-1*line.second.y()*sizey);
            p.translate(line.first.x()*sizex,-1*line.first.y()*sizey);
            p.drawText(QRect(-10,0,60,40), Qt::AlignCenter, "("+QString::number(line.first.x())+","+QString::number(line.first.y())+")");
            p.translate(-line.first.x()*sizex, line.first.y()*sizey);
            if(line.first!=line.second){
            p.translate(line.second.x()*sizex,-1*line.second.y()*sizey);
             p.drawText(QRect(-5,0,40,30), Qt::AlignCenter, "("+QString::number(line.second.x())+","+QString::number(line.second.y())+")");
             p.translate(-line.second.x()*sizex,line.second.y()*sizey);
            }

     }

     else
     {

            p.drawEllipse((brc.getx()-brc.getrad())*sizex, (-brc.gety()-brc.getrad())*sizey,2*brc.getrad()*sizex, 2*brc.getrad()*sizey);
            p.translate(brc.getx()*sizex, -brc.gety()*sizey);
             p.setBrush(Qt::black);
            p.drawEllipse(-sizex/8,-sizex/8,sizex/4,sizex/4);
             p.drawText(QRect(-30,0,60,65), Qt::AlignCenter, "("+QString::number(brc.getx())+","+QString::number(brc.gety())+")"+"\nr="+QString::number(brc.getrad()));
            p.translate(-line.second.x()*sizex,line.second.y()*sizey);
     //else ui->label->setText(QString::number(brc.getx()));


    }
    }


}

void MainWindow::turnBack()
{
    draw =0;
    this->repaint();
    ui->back->hide();
    ui->brc->show();
    ui->brs->show();
    ui->dda->show();

    ui->naive->show();

    ui->label->setText("Choose algorithm");
    setFixedSize(800,540);

}
